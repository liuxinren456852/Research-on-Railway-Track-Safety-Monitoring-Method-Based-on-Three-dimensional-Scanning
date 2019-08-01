#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <iostream>
#include <QtGui>
#include <QString>
#include <QtWidgets>
#include <QApplication>
#include <QStyle>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSplitter>
//#include <QVTKWidget2.h>
#include <QOpenGLWidget>
#include <vtkRenderWindow.h>
#include <vtkOutputWindow.h>
#include <QFileDialog>
//#include <vtkWin32OutputWindow.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include "button.h"
#include "point_cloud v1.0.1.h"
#include "load.h"
#include "qlcdnum.h"
#include "button.h"
#include "viewer.h"
#include <QCloseEvent>
#include <QMessageBox>
#define TILE_SIZE 10

using namespace std;
using namespace pcl;

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	void closeEvent(QCloseEvent *event);
    ~MainWindow();
private slots:
    void adjustViewSize();
	void openFile();
	void saveFile();
private:
	PointCloudViewer *viewer_main;
	//PointCloudViewer *viewer2;
	pcl::visualization::PCLVisualizer *viewer;
	PointCloud<pcl::PointXYZRGB>::Ptr cloud;
	//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	//PointCloudViewer *viewer_open;
	QSplitter *splitter;

	//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

	PointCloudMain *point_cloud_main;

    void initScene();
    void initSceneBackground();

	LCDNumber *number;
	LCDAlarm *alarm;
	
    QGraphicsScene *scene;
    QGraphicsView *view;
	QToolBar *toolBar;
    //监测按钮
	SavePointFile *save_button;
	OpenPointFile *open_button;
	KeepDetect *keep_button;
	StartDetect *start_button;
	PauseDetect *pause_button;
	ShowDifferPoint *differ_button;
	ShowClusterPoint *cluster_button;
	ResetView *reset_button;
};

#endif // MAINWINDOW_H
