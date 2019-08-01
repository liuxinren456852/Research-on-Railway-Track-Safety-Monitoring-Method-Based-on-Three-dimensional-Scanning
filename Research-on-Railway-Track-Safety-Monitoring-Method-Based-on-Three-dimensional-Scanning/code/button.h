#ifndef BUTTON_THREAD
#define BUTTON_THREAD
#pragma once

#include <QThread>
#include "point_cloud v1.0.1.h"
#include <QObject>
#include <QtWidgets>

class StartDetect : public QObject
{
	Q_OBJECT
public:
	StartDetect(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~StartDetect() = default;
	QAction* getButton() { return start_action; }
private:
	QAction *start_action;
};

class PauseDetect : public QObject
{
	Q_OBJECT
public:
	PauseDetect(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~PauseDetect() = default;
	QAction* getButton() { return pause_action; }
private:
	QAction *pause_action;
};

class KeepDetect : public QObject
{
	Q_OBJECT
public:
	KeepDetect(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~KeepDetect() = default;
	QAction* getButton() { return keep_action; }
private:
	QAction *keep_action;
};

class OpenPointFile : public QObject
{
	Q_OBJECT
public:
	OpenPointFile(QWidget *window, QMenu *menu, QToolBar *tool);
	~OpenPointFile() = default;
	QAction* getButton() { return open_action; }
private:
	QAction *open_action;
};


class SavePointFile : public QObject
{
	Q_OBJECT
public:
	SavePointFile(QWidget *window,  QMenu *menu, QToolBar *tool);
	~SavePointFile() = default;
	QAction* getButton() { return save_action; }
private:
	QAction *save_action;
};

class ShowDifferPoint : public QObject
{
	Q_OBJECT
public:
	ShowDifferPoint(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~ShowDifferPoint() = default;
	QAction* getButton() { return differ_action; }
private:
	QAction *differ_action;
};

class ShowClusterPoint : public QObject
{
	Q_OBJECT
public:
	ShowClusterPoint(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~ShowClusterPoint() = default;
	QAction* getButton() { return cluster_action; }
private:
	QAction *cluster_action;
};

class ResetView : public QObject
{
	Q_OBJECT
public:
	ResetView(QWidget *window, PointCloudMain *point, QMenu *menu, QToolBar *tool);
	~ResetView() = default;
	QAction* getButton() { return reset_action; }
private:
	QAction *reset_action;
};

#endif // !BUTTON_THREAD