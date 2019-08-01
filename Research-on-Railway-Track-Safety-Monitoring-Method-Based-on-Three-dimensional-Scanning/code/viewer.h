#ifndef VIEWER_H
#define VIEWER_H
#pragma once
#include "pch.h"
#include <pcl/visualization/cloud_viewer.h>  
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <QWidget>
#include <fstream>
#include <vector>
#include <QDebug>
#include <string>
//#include <QLabel>
#include <vtkAutoInit.h> 

VTK_MODULE_INIT(vtkRenderingOpenGL)

VTK_MODULE_INIT(vtkInteractionStyle);

VTK_MODULE_INIT(vtkRenderingFreeType);

using namespace std;
using namespace pcl;

class PointCloudViewer : public QWidget
{
	Q_OBJECT
public:
	PointCloudViewer(QWidget *window);
	PointCloudViewer(QWidget *window, PointCloud<PointXYZRGB>::Ptr &result);
	~PointCloudViewer() = default;
	QVTKWidget *getWidget();
	bool showPointCloud();
	//bool showPointCloud(PointCloud<PointXYZRGB>::Ptr &point);
	//bool showPointCloud(PointCloud<PointXYZRGB>::Ptr point);
	PointCloud<PointXYZRGB>::Ptr getPointCloud();
	//boost::shared_ptr<pcl::visualization::PCLVisualizer> getViewer() { return viewer; }
	pcl::visualization::PCLVisualizer::Ptr getViewer() { return viewer; }
	bool showPointCloud(const PointCloud<PointXYZRGB>::Ptr &point_cloud_origin, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ);
	void resetView();
	void showView() {emit ViewShowOver();}
signals:
	void ViewShowOver();
public slots:
	void updatePointCloud(const PointCloud<PointXYZRGB>::Ptr &point_cloud_actual, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ);
private:
	PointCloud<PointXYZRGB>::Ptr background;
	PointCloud<PointXYZRGB>::Ptr foreground;
	PointCloud<PointXYZRGB> background_tem;
	PointCloud<PointXYZRGB> foreground_tem;
	//shared_ptr<PointCloud<PointXYZRGB>::Ptr> background;
	//shared_ptr<PointCloud<PointXYZRGB>::Ptr> foreground;
	//PointCloud<PointXYZRGB>::Ptr target_xyz;
	//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	pcl::visualization::PCLVisualizer::Ptr viewer;
	//pcl::visualization::PCLVisualizer *viewer;
	QVTKWidget *QTVK_widget;
	//GlobalWarningDisplayOff();
	//QLabel* label;
};

#endif