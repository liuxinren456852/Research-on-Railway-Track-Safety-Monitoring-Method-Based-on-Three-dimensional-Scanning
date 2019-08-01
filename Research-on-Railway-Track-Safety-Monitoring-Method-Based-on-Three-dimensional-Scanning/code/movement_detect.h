#ifndef MOVEMENT_DETECT
#define MOVEMENT_DETECT
#pragma once
#include "pre_fliter.h"
#include <iostream>
#include <vector>
#include <fstream> 
#include "load.h"
#include <algorithm>
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

using namespace std;
using namespace pcl;

/*
类Movement_Detect 主要用于运动物体检测
友元函数FrameDifferenceRoute（） 用于求得两帧pcd文件之间的差异
函数MovementObject（）用于检测是否有目标运动物体
参数frame_one frame_two frame_defference分别存储第一帧、第二帧和差异帧点云
*/

class Movement_Detect 
{
	friend bool FrameDifferenceRoute(Movement_Detect target); 
public:
	Movement_Detect();
	Movement_Detect(PointCloud<PointXYZI>::Ptr &one, PointCloud<PointXYZI>::Ptr &two);
	~Movement_Detect() = default;
	bool MovementObject();
private:
	int roi_num = 0;
	int	not_roi_num = 0;
	// bool gaussian_fliter();
	bool euclidean_algorithm();
	PointCloud<PointXYZI>::Ptr frame_one;
	PointCloud<PointXYZI>::Ptr frame_difference;
};
#endif


