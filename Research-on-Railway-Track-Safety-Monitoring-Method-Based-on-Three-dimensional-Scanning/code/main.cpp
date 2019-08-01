#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QWidget w;
	MainWindow win;
	//Detect detect(&w);
	//win.show();
	win.showMaximized();
	return a.exec();
}
