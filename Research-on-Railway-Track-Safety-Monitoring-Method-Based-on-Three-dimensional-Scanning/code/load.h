#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include <vector>
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>

using namespace std;
using namespace pcl;

/*
类Get_Point_Cloud 主要用于加载pcd图像
友元函数LoadPointCloud（）用于加载下一个文件 参数next_file决定是否加载下一个
函数GetPointCloudName()用于获取文件夹中的文件列表
参数in_path用于设置文件目录
参数point_cloud_name记录所有文件名称
函数GetPointCloud()用于获取列表并存储于point_cloud_name中
*/

class PointCloudFile
{
	friend PointCloud<PointXYZRGB>::Ptr loadPointCloud(PointCloudFile target);
public:
	PointCloudFile();
	PointCloudFile(string file_path);  //包含自定义路径的构造函数
	~PointCloudFile() = default;
	vector<string> getPointCloudName(); //返回目录中文件的名称列表
	//string getFileName();
private:
	string in_path;  //路径名
	vector<string> point_cloud_name; //文件名称列表
	bool getPointCloud(); //加载路径中文件列表
	vector<_finddata_t> point_cloud_file; //点云文件信息序列，包含创建时间等信息
	struct _finddata_t fileinfo;
	string curr;  //当前路径
	long long handle;
};

