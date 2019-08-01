#ifndef MOVEMENT_DETECT_GAUSSIAN
#define MOVEMENT_DETECT_GAUSSIAN

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

class Movement_Detect_Gaussian
{
public:
	bool MovementObject();
	Movement_Detect_Gaussian();
	Movement_Detect_Gaussian(PointCloud<PointXYZI>::Ptr &one, PointCloud<PointXYZI>::Ptr &two);
	~Movement_Detect_Gaussian() = default;
private:
	int euclidean_algorithm(PointCloud<PointXYZI>::Ptr frame);
	PointCloud<PointXYZI>::Ptr frame_one;
	PointCloud<PointXYZI>::Ptr frame_two;
};
#endif