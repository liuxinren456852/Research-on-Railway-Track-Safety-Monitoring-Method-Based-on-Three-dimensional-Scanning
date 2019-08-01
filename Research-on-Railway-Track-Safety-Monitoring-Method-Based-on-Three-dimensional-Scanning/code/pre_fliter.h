#ifndef PRE_FLITER
#define PRE_FLITER

#pragma once
#include <vector>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

using namespace std;
using namespace pcl;

/*
类Point_Cloud_Fliter，主要用于滤波
函数fliter()用于分别调用直接滤波和高斯滤波
函数get_point_cloud()返回滤波后的点云
参数point_cloud保存滤波后的点云
函数stright_fliter()和gaussian_fliter()分别实现直接滤波和高斯滤波
*/

class PointCloudFliter
{
public:
	PointCloudFliter();
	PointCloudFliter(PointCloud<PointXYZRGB>::Ptr &point_cloud_input);
	~PointCloudFliter() = default;
	bool fliterPointCloud();
	bool fliterPointCloud(PointCloud<PointXYZRGB>::Ptr &point_cloud_input);
	PointCloud<PointXYZRGB>::Ptr getPointCloud();
private:
	PointCloud<PointXYZRGB>::Ptr point_cloud;  //点云对象，用输入的点云进行初始化
	bool stright_fliter();
	bool gaussian_fliter();
};
#endif