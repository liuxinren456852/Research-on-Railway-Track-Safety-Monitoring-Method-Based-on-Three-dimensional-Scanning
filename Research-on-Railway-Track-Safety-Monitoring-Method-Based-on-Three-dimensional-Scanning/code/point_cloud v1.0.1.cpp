/// 差分法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "point_cloud v1.0.1.h"
#include <QFile>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
//#include <ctime>

using namespace pcl;
using namespace std;

PointCloudMain::PointCloudMain():point_cloud_origin(new pcl::PointCloud<pcl::PointXYZRGB>),
			point_cloud_actual(new pcl::PointCloud<pcl::PointXYZRGB>),
			point_cloud_differ(new pcl::PointCloud<pcl::PointXYZRGB>),
			showtype(true), waitting(false){ }
PointCloudMain::PointCloudMain(PointCloudViewer *viewer_main) :
	point_cloud_origin(new pcl::PointCloud<pcl::PointXYZRGB>),
	point_cloud_actual(new pcl::PointCloud<pcl::PointXYZRGB>),
	point_cloud_differ(new pcl::PointCloud<pcl::PointXYZRGB>),
	showtype(true), waitting(false), viewer_main(viewer_main) { }
PointCloudMain::~PointCloudMain() {}

void PointCloudMain::startThread()
{
	//vector<string> safe_name;
	//clock_t startTime, endTime;
	//startTime = clock();
	//if ((pcl::io::loadPCDFile<pcl::PointXYZRGB>("D:\\20180125142143834_back.pcd", *point_cloud_origin)) == -1)
	//if ((pcl::io::loadPCDFile<pcl::PointXYZRGB>("D:\\20180125142133333.pcd",*point_cloud_origin))== -1)
	if ((pcl::io::loadPCDFile<pcl::PointXYZRGB>("D:\\foreground.pcd", *point_cloud_origin)) == -1)
	{
		PCL_ERROR("Couldn't read file pcd\n");
	}
	//Eigen::Vector4f rotation = point_cloud_origin->sensor_origin_();
	point_cloud_fliter.fliterPointCloud(point_cloud_origin);
	//QFile file(QObject::tr("D:\\difile.txt"));
	//file.open(QIODevice::WriteOnly | QIODevice::Append);
	//QTextStream out(&file);
	//vector<string> *safe_list;
	//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));//
	//point_cloud_actual.reset(new pcl::PointCloud<pcl::PointXYZRGB>);//
	//viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));//
	//viewer->addPointCloud<pcl::PointXYZRGB>(point_cloud_actual, "background");//
	//for (size_t i = 0; i < 13; i++)
	int rate = 0;
	for (size_t i = 0; i < point_cloud_list.size(); i++)
	{
		//boost::unique_lock<PointCloud<PointXYZRGB>::Ptr> lock(point_cloud_differ);
		point_cloud_actual = loadPointCloud(point_cloud_file);
		point_cloud_fliter.fliterPointCloud(point_cloud_actual);
		//qDebug() << "result" << endl;
		result = movement_detect_octree.detectMovement(point_cloud_origin, point_cloud_actual);
		//point_cloud_differ = movement_detect_octree.getDifferCloud();
		if(showtype) point_cloud_differ = movement_detect_octree.getDifferCloud();
		else if(!showtype) point_cloud_differ = movement_detect_octree.getCloudClusterResult();

		//viewer_main->showPointCloud(point_cloud_actual);
		//viewer_main->showPointCloud(point_cloud_actual, movement_detect_octree.getPointNum());
		//g_lock.lock();
		viewshow = false;
		viewer_main->showPointCloud(point_cloud_origin, point_cloud_differ);
		//viewer->updatePointCloud<pcl::PointXYZRGB>(point_cloud_actual, "background");//
		if (1 == i) viewer_main->resetView();
		//Sleep(1);
		//g_lock.unlock();
		//movement_detect_octree.clearCloudClusterResult();
		//if (result)   out << QString::fromStdString(point_cloud_list.at(i)) << endl;
		//if (result) rate++;
		//if (result) safe_name.push_back(point_cloud_list.at(i));
		if (result) sendSafeFlag();
		else sendWarnFlag();
		//if (result) qDebug()<< QString::fromStdString(point_cloud_list.at(i)) <<"!!!!!!!!!!!!!!!"<<endl;
		sendFileNum();
		//qDebug() << point_cloud_actual->size() << endl;
		//qDebug() << point_cloud_differ->size() << endl;
		while(!viewshow) Sleep(1);
		//sendNewViewer();
		Sleep(1);
		while (waitting) Sleep(1);
		movement_detect_octree.clearPointNum();
	}
	//ofstream ofile("D:\\difile.txt", ofstream::out);
	//for (auto fliter = (safe_list->begin()); fliter != (safe_list->end()); )
	//{
		//out << QString::fromStdString(*fliter) << endl;
		//ofile << (*fliter) << endl;
		//auto name = "safe " + *fliter;
		//cout << "safe" << (*fliter).c_str() << endl;
	//}
	//ofile.close();
	//file.flush();
	//file.close();
	//sendOverFlag();
	//endTime = clock();
	//ofstream ofile("D:\\difile.txt", ofstream::out);
	//for (auto it = safe_name.begin(); it != safe_name.end(); it++)
	//{
	//	qDebug() << QString::fromStdString(*it) << endl;
	//}
	//ofile.close();
	//qDebug() << "The run time is: " << rate << endl;
	//qDebug() << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << "done!\n";
}

void PointCloudMain::startDetect()
{
	//startThread();
	waitting = false;
	//qDebug() << "thread&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	//RunOver();
	QEventLoop loop;
	connect(this, &PointCloudMain::RunOver, &loop, &QEventLoop::quit);
	std::thread start = std::thread(std::mem_fn(&PointCloudMain::startThread), this);
	//start.join();
	start.detach();
	//loop.exec();
}


void PointCloudMain::pauseDetect()
{
	waitting = true;
	//system("PAUSE");
}

void PointCloudMain::keepDetect()
{
	waitting = false;
	//system("PAUSE");
}

void PointCloudMain::showDiffer()
{
	showtype = true;
}

void PointCloudMain::showCluster()
{
	showtype = false;
}

void PointCloudMain::resetView()
{
	viewer_main->resetView();
}

void PointCloudMain::keepShow()
{
	viewshow = true;
}