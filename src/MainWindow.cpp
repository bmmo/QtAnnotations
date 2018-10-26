#include "include/MainWindow.h"
#include <OSGWidget.h>

#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags)
{

	this->setCentralWidget(new OSGWidget(this));
}

MainWindow::~MainWindow()
{
}


