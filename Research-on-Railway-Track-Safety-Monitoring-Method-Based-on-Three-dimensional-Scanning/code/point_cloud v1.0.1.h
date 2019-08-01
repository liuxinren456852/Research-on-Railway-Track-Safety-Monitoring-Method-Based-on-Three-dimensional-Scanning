#ifndef POINT_CLOUD
#define POINT_CLOUD
#pragma once
#include <QDebug>
#include <QString>
#include <QObject>
#include "pch.h"
#include "pre_fliter.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "viewer.h"
#include <fstream> 
#include <windows.h>
#include "load.h"
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <thread>
#include <string>
#include <pcl/point_types.h>
//#include <mutex>
#include <QEventLoop>
//#include "movement_detect.h"
//#include "movement_detect_gaussian.h"
#include "movement_detect_octree.h"

class PointCloudMain : public QObject
{
	Q_OBJECT
public:
	PointCloudMain();
	PointCloudMain(PointCloudViewer *viewer_main);
	~PointCloudMain();
	//void pause();
	void startThread();
	void sendFileNum() { emit FileNum(); }
	void sendOverFlag() { emit RunOver(); }
	void sendSafeFlag() { emit SafeFlag(); }
	void sendWarnFlag() { emit WarnFlag(); }
	void sendNewViewer() { emit NewViewer(point_cloud_actual, point_cloud_differ); }
public slots:
	void startDetect();
	void pauseDetect();
	void keepDetect();
	void showDiffer();
	void showCluster();
	void resetView();
	void keepShow();
signals:
	void FileNum();
	void RunOver();
	void SafeFlag();
	void WarnFlag();
	void NewViewer(const PointCloud<PointXYZRGB>::Ptr &point_cloud_actual, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ);
private:
	PointCloudViewer *viewer_main; //视窗1，显示当前点云
	//PointCloudViewer *viewer2; //视窗2，显示差异点云
	PointCloudFile point_cloud_file; //读取文件列表类
	PointCloudFliter point_cloud_fliter; //点云过滤预处理类
	MovementDetectOctree movement_detect_octree; //运动检测类
	vector<string> point_cloud_list = point_cloud_file.getPointCloudName(); //文件列表
	PointCloud<PointXYZRGB>::Ptr point_cloud_origin, point_cloud_actual, point_cloud_differ; //背景点云和当前点云
	bool showtype; //控制显示差异点（true）还是点云团（false）
	bool waitting;  //进行暂停与继续的控制
	bool result; //检测结果变量
	bool viewshow;
};

#endif