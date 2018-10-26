#include <OSGWidget.h>
#include <ShapeFactory.h>

#include <QMouseEvent>
#include <QPainter>
#include <QEvent>

#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/StateSet>
#include <osg/Group>
#include <osgGA/TrackballManipulator>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

void OSGWidget::Viewer::setupThreading()
{

	if( _threadingModel == SingleThreaded )
	{
		if(_threadsRunning)
			stopThreading();
	}
	else
	{
		if(!_threadsRunning)
			startThreading();
	}

}

OSGWidget::OSGWidget(QWidget* parent, Qt::WindowFlags f):
	QOpenGLWidget(parent, f),
	m_graphicsWindow(new osgViewer::GraphicsWindowEmbedded(
				this->x(), this->y(), this->width(), this->height()
				)
			),
	m_viewer(new Viewer)
{

	float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
	auto pixelRatio   = this->devicePixelRatio();

	osg::Camera* camera = new osg::Camera;
	camera->setViewport(0, 0, this->width() * pixelRatio, this->height() * pixelRatio);
	camera->setClearColor(osg::Vec4( 0.f, 0.f, 0.f, 1.f ));
	camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f);
	camera->setGraphicsContext(m_graphicsWindow);

	osgViewer::View* view = new osgViewer::View;
	view->setCamera(camera);

	osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
  manipulator->setAllowThrow( false );

  view->setCameraManipulator( manipulator );

	
	m_viewer->addView(view);
	m_viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
	m_viewer->realize();

	this->setFocusPolicy( Qt::StrongFocus );
	this->setMinimumSize( 100, 100 );

	this->setMouseTracking( true );


	setupRootNode(view);
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
	this->makeCurrent();

	QPainter painter( this );
	painter.setRenderHint( QPainter::Antialiasing );

	this->paintGL();

	painter.end();

	this->doneCurrent();
}

void OSGWidget::paintGL()
{
  m_viewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
  this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  m_graphicsWindow->resized( this->x(), this->y(), width, height );

  this->onResize( width, height );
}

bool OSGWidget::event( QEvent* event )
{
  bool handled = QOpenGLWidget::event( event );

  // This ensures that the OSG widget is always going to be repainted after the
  // user performed some interaction. Doing this in the event handler ensures
  // that we don't forget about some event and prevents duplicate code.
  switch( event->type() )
  {
  case QEvent::KeyPress:
  case QEvent::KeyRelease:
  case QEvent::MouseButtonDblClick:
  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
  case QEvent::MouseMove:
  case QEvent::Wheel:
    this->update();
    break;

  default:
    break;
  }

  return handled;
}

void OSGWidget::onResize( int width, int height )
{

  std::vector<osg::Camera*> cameras;
  m_viewer->getCameras( cameras );

  auto pixelRatio = this->devicePixelRatio();

  cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );

}

void OSGWidget::onHome()
{

	osgViewer::ViewerBase::Views views;
	m_viewer->getViews(views);

	for( std::size_t i = 0; i < views.size(); i++ )
	{
		osgViewer::View* view = views.at(i);
		view->home();
	}

}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
  osgGA::EventQueue* eventQueue = m_graphicsWindow->getEventQueue();

  if( eventQueue )
    return eventQueue;
  else
    throw std::runtime_error( "Unable to obtain valid event queue");
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{

	auto pixelRatio = this->devicePixelRatio();

	this->getEventQueue()->mouseMotion( static_cast<float>( event->x() * pixelRatio ),
			static_cast<float>( event->y() * pixelRatio ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
{
	// 1 = left mouse button
	// 2 = middle mouse button
	// 3 = right mouse button

	unsigned int button = 0;

	switch( event->button() )
	{
		case Qt::LeftButton:
			button = 1;
			break;

		case Qt::MiddleButton:
			button = 2;
			break;

		case Qt::RightButton:
			button = 3;
			break;

		default:
			break;
	}

	auto pixelRatio = this->devicePixelRatio();

	this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() * pixelRatio ),
			static_cast<float>( event->y() * pixelRatio ),
			button );
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
	// 1 = left mouse button
	// 2 = middle mouse button
	// 3 = right mouse button

	unsigned int button = 0;

	switch( event->button() )
	{
		case Qt::LeftButton:
			button = 1;
			break;

		case Qt::MiddleButton:
			button = 2;
			break;

		case Qt::RightButton:
			button = 3;
			break;

		default:
			break;
	}

	auto pixelRatio = this->devicePixelRatio();

	this->getEventQueue()->mouseButtonRelease( static_cast<float>( pixelRatio * event->x() ),
			static_cast<float>( pixelRatio * event->y() ),
			button );
}

void OSGWidget::wheelEvent( QWheelEvent* event )
{

	event->accept();
	int delta = event->delta();

	osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
		: osgGA::GUIEventAdapter::SCROLL_DOWN;

	this->getEventQueue()->mouseScroll( motion );
}

void OSGWidget::setupRootNode(osgViewer::View* view) 
{

	m_root = new osg::Group;

	osg::StateSet* ss = m_root->getOrCreateStateSet();

	// Enable depth testing
	ss->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	ss->setMode(GL_LIGHTING,   osg::StateAttribute::OFF);

	// Debug
	m_root->addChild(ShapeFactory::Sphere(osg::Vec3f(0.f, 0.f, 0.f), 10.f, osg::Vec4f(1.f, 1.f, 1.f, 1.f)));
	m_root->addChild(ShapeFactory::Quad(osg::Vec3f(0.f, 0.f, 0.f), 10.f, 10.f, osg::Vec4f(0.f, 1.f, 0.f, 1.f)));

	view->setSceneData(m_root);

	onHome();

}

