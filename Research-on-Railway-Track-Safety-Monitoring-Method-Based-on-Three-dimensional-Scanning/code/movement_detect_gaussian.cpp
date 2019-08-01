#include "pch.h"
#include "movement_detect_gaussian.h"

Movement_Detect_Gaussian::Movement_Detect_Gaussian(){}
Movement_Detect_Gaussian::Movement_Detect_Gaussian(PointCloud<PointXYZI>::Ptr &one, 
	PointCloud<PointXYZI>::Ptr &two):frame_one(one),frame_two(two){}

int Movement_Detect_Gaussian::euclidean_algorithm(PointCloud<PointXYZI>::Ptr frame)
{
	//cout << frame_difference->size() << endl;
	search::KdTree<PointXYZI>::Ptr tree(new search::KdTree<PointXYZI>);
	tree->setInputCloud(frame);
	//被分割出来的点云团（标号队列）
	vector<PointIndices> cluster_indices;
	//欧式分割器
	EuclideanClusterExtraction<PointXYZI> ec;
	ec.setClusterTolerance(0.10); // 2cm
	ec.setMinClusterSize(6);
	ec.setMaxClusterSize(10000);
	//搜索策略树
	ec.setSearchMethod(tree);
	ec.setInputCloud(frame);
	ec.extract(cluster_indices);
	int j = 0;
	//pcl::PCDWriter writer;
	for (auto it = cluster_indices.begin(); it != cluster_indices.end(); it++)
	{
		PointCloud<PointXYZI>::Ptr cloud_cluster(new PointCloud<PointXYZI>);
		for (auto point = it->indices.begin(); point != it->indices.end(); point++)
			cloud_cluster->points.push_back(frame->points[*point]); //*
		cloud_cluster->width = cloud_cluster->points.size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;
		//std::stringstream ss;
		//ss << "./result/cloud_cluster_" << j << ".pcd";
		//writer.write<pcl::PointXYZI>(ss.str(), *cloud_cluster, false); //*
		++j;
		//cout << j << endl;
	}
	return j;
}

bool Movement_Detect_Gaussian::MovementObject()
{
	cout << euclidean_algorithm(frame_one) << endl;
	cout << euclidean_algorithm(frame_two) << endl;
	if (euclidean_algorithm(frame_one) == euclidean_algorithm(frame_two))
	{
		cout << "safe..." << endl;
		return true;
	}
	else
	{
		cout << "warn..." << endl;
		return false;
	}
}