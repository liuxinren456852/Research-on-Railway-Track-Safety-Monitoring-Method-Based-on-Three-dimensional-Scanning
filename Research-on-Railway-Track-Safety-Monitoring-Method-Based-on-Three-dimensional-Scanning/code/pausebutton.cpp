#include "pausebutton.h"

PAUSE::PAUSE(QWidget *window) : pauseaction(new QAction(QIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause)),
	QStringLiteral("ÔÝÍ£"), window))
{
	pauseaction->setShortcut(tr("ctrl+p"));
	//pauseAction->setStatusTip(tr("Save a new file"));
}
