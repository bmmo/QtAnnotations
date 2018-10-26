#ifndef _INCLUDE_MAINWINDOW_H_
#define _INCLUDE_MAINWINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow 
{

	Q_OBJECT

public:

	MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
	virtual ~MainWindow();

};


#endif
