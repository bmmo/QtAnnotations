#include <MainWindow.h>

#include <QSurfaceFormat>
#include <QApplication>

#include <MainWindow.h>

int main(int argc, char** argv) 
{

	QApplication app(argc, argv);

	// Set OpenGL profile
	QSurfaceFormat format;
	format.setVersion(2, 1);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);

	QSurfaceFormat::setDefaultFormat(format);

	MainWindow w;
	w.show();

	return app.exec();

}

