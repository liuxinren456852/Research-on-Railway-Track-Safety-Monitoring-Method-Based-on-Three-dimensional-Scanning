#ifndef MAIN_WINDOW_THREAD
#define MAIN_WINDOW_THREAD
#pragma once

#include <QThread>

class MainWindowThread : public QThread 
{
public:
	virtual void run();
};

void MainWindowThread::run()
{
	for (int count = 0; count < 20; count++) 
	{
		sleep(1);
		qDebug("Ping!");
	}
}

#endif // !BUTTON_THREAD


