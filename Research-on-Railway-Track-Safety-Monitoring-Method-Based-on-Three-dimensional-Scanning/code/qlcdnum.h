#pragma once
#include <QObject>
#include <QtWidgets>
#include <QString>

class LCDNumber : public QObject
{
	Q_OBJECT
public:
	LCDNumber();
	~LCDNumber() = default;
	QLCDNumber *getNumber() { return number; }
public slots:
	void displayNumber();
private:
	QLCDNumber *number;
};

class LCDAlarm : public QObject
{
	Q_OBJECT
public:
	LCDAlarm();
	~LCDAlarm() = default;
	QLCDNumber *getAlarm() { return alarm; }
public slots:
	void displaySafe();
	void displayWarn();
private:
	QLCDNumber *alarm;
};
