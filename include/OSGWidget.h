#ifndef _INCLUDE_OSG_WIDGET
#define _INCLUDE_OSG_WIDGET

#include <QOpenGLWidget>

#include <osg/ref_ptr>
#include <osg/Group>
#include <osgViewer/View>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

class OSGWidget : public QOpenGLWidget
{

	Q_OBJECT

public:

	OSGWidget(QWidget* parent, Qt::WindowFlags f = 0);

	virtual ~OSGWidget();


protected:

	void setupRootNode(osgViewer::View* view);

	virtual void paintEvent(QPaintEvent* paintEvent);
	virtual void paintGL();
	virtual void resizeGL(int width, int height);
	virtual bool event(QEvent* event);


	virtual void onResize(int width, int height);
	virtual void onHome();

	virtual void mouseMoveEvent( QMouseEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
	virtual void mouseReleaseEvent( QMouseEvent* event );
	virtual void wheelEvent( QWheelEvent* event );

	osgGA::EventQueue* getEventQueue() const;


	class Viewer : public osgViewer::CompositeViewer
	{
		public:
			virtual void setupThreading();
	};

	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_graphicsWindow;
	osg::ref_ptr<Viewer>                            m_viewer;
	osg::ref_ptr<osg::Group>                        m_root;

};


#endif
