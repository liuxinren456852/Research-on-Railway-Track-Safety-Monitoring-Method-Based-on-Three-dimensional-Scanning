#include "qlcdnum.h"

LCDNumber::LCDNumber() :number(new QLCDNumber())
{
	number->setObjectName(QStringLiteral("Ö¡ĞòºÅ"));
	//number->setGeometry(0, 65, 100, 100);
	number->setDigitCount(3);
	number->setDecMode();
	number->display(001);
	number->setMinimumSize(100, 100);
	number->setMaximumSize(200, 200);
	number->setStyleSheet("background:yellow");
};

void LCDNumber::displayNumber()
{
	static int num = 0;
	num++;
	number->display(num);
	number->repaint();
}

LCDAlarm::LCDAlarm() :alarm(new QLCDNumber())
{
	alarm->setObjectName(QStringLiteral("Ö¡ĞòºÅ"));
	//alarm->move(50, 50);
	//alarm->setGeometry(0, 0, 100, 100);
	alarm->setDigitCount(4);
	alarm->setMinimumSize(100, 100);
	alarm->setMaximumSize(200, 200);
	//alarm->setDecMode();
	alarm->display(tr("SAFE"));
	
	alarm->setStyleSheet("background:cyan");
};

void LCDAlarm::displaySafe()
{
	alarm->setStyleSheet("background:cyan");
	alarm->display(tr("SAFE"));
	alarm->repaint();
}

void LCDAlarm::displayWarn()
{
	alarm->setStyleSheet("background:red");
	alarm->display(tr("ALAR"));
	alarm->repaint();
}