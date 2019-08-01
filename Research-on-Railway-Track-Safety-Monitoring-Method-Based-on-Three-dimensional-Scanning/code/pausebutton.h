#pragma once
#include <QObject>
#include <QtWidgets>

class PAUSE : public QObject
{
	Q_OBJECT
public:
	PAUSE(QWidget *window);
	~PAUSE() = default;
	//void send() { emit filename(); }
	QAction *pauseaction;
signals:
	void pause();
//private:

};
