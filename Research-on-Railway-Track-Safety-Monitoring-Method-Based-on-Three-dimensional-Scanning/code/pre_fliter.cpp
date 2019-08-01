#include "pch.h"
#include "pre_fliter.h"
using namespace std;

PointCloudFliter::PointCloudFliter() {};

PointCloudFliter::PointCloudFliter
(PointCloud<PointXYZRGB>::Ptr &point_cloud_input):point_cloud(point_cloud_input) {}

//public函数，调用private函数进行直接滤波和高斯滤波
bool PointCloudFliter::fliterPointCloud()
{
	if (stright_fliter() && gaussian_fliter())
		return true;
}

bool PointCloudFliter::fliterPointCloud(PointCloud<PointXYZRGB>::Ptr & point_cloud_input)
{
	point_cloud = point_cloud_input;
	if (stright_fliter() && gaussian_fliter())
		return true;
}

//private函数，直接滤波
bool PointCloudFliter::stright_fliter()
{
	for (auto fliter = (point_cloud->begin()); fliter != (point_cloud->end()); )
	{
		/*
		//测试代码
		if (((*fliter).x >= 4.3) || ((*fliter).x <= 3.7)) { fliter = point_cloud->erase(fliter); }
		else if (((*fliter).y >= 14.4) || ((*fliter).y <= 13.9)) { fliter = point_cloud->erase(fliter); }
		else if (((*fliter).z >= 2.9) || ((*fliter).z <= 2.8)) { fliter = point_cloud->erase(fliter); }
		fliter++;
		*/
		
		//正确代码
		//(*fliter).r = 255;
		//(*fliter).g = 255;
		//(*fliter).b = 255;
		if ((*fliter).x >= 15 || (*fliter).x <= -50)  fliter = point_cloud->erase(fliter); 
		else if((*fliter).y >= 18 || (*fliter).y <= -5)  fliter = point_cloud->erase(fliter); 
		else if ((*fliter).z >= 8 )  fliter = point_cloud->erase(fliter); 
		else if((*fliter).x >= 8 && (*fliter).y >= 12) fliter = point_cloud->erase(fliter);
		fliter++;
	}
	return true;
}

//private函数，高斯滤波
bool PointCloudFliter::gaussian_fliter()
{
	StatisticalOutlierRemoval<PointXYZRGB> sor;
	sor.setInputCloud(point_cloud);
	sor.setMeanK(20);//近邻点个数50
	sor.setStddevMulThresh(3);
	sor.filter(*point_cloud);
	return true;
}

//public函数，返回点云对象
PointCloud<PointXYZRGB>::Ptr PointCloudFliter::getPointCloud()
{
	return point_cloud;
};



