#include "pch.h"
#include "movement_detect.h"

Movement_Detect::Movement_Detect() {}
Movement_Detect::Movement_Detect(PointCloud<PointXYZI>::Ptr &one, 
	PointCloud<PointXYZI>::Ptr &two):frame_one(one),frame_difference(two){}

bool Movement_Detect::MovementObject()
{
	//for (auto it : *frame_difference) cout << it << endl;
	//cout << frame_difference->size()  << endl;
	if (!FrameDifferenceRoute(*this)) { cout << "safe..." << endl; return false; }
	else
	{
		if(euclidean_algorithm()) { cout << "warn!!!" << endl;  return true; }
		else { cout << "safe..." << endl;  return false; }
		/*
		for (auto differ = frame_difference->begin(); differ != frame_difference->end(); differ++)
		{
			if (((*differ).x < -21) || ((*differ).x > 10))  not_roi_num++;
			else if (((*differ).y < 8) || ((*differ).y > 17))  not_roi_num++;
			else if (((*differ).z < -1) || ((*differ).z > 7))  not_roi_num++;
			else roi_num++;
		}
		if (roi_num >= 6) { cout << "warn!!!" << endl;  return true; }
		else if (not_roi_num >= 15) { cout << "warn!!!" << endl;  return true; }
		else { cout << "safe..." << endl;  return false; }
		*/
	}
}

/*
bool Movement_Detect::gaussian_fliter() 
{
	StatisticalOutlierRemoval<PointXYZI> sor;
	sor.setInputCloud(frame_difference);
	sor.setMeanK(5);//近邻点个数50
	sor.setStddevMulThresh(0.01);
	sor.filter(*frame_difference);
	return true;
}
*/

bool Movement_Detect::euclidean_algorithm()
{
	//cout << frame_difference->size() << endl;
	search::KdTree<PointXYZI>::Ptr tree(new search::KdTree<PointXYZI>);
	tree->setInputCloud(frame_difference);
	//被分割出来的点云团（标号队列）
	vector<PointIndices> cluster_indices;
	//欧式分割器
	EuclideanClusterExtraction<PointXYZI> ec;
	ec.setClusterTolerance(0.35); // 2cm
	ec.setMinClusterSize(6);
	ec.setMaxClusterSize(50);
	//搜索策略树
	ec.setSearchMethod(tree);
	ec.setInputCloud(frame_difference);
	ec.extract(cluster_indices);
	int j = 0;
	//pcl::PCDWriter writer;
	for (auto it = cluster_indices.begin(); it != cluster_indices.end(); it++)
	{
		PointCloud<PointXYZI>::Ptr cloud_cluster(new PointCloud<PointXYZI>);
		for (auto point = it->indices.begin(); point != it->indices.end(); point++)
			cloud_cluster->points.push_back(frame_difference->points[*point]); //*
		cloud_cluster->width = cloud_cluster->points.size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;
		//std::stringstream ss;
		//ss << "./result/cloud_cluster_" << j << ".pcd";
		//writer.write<pcl::PointXYZI>(ss.str(), *cloud_cluster, false); //*
		++j;
		//cout << j << endl;
	}
	if (j == 0) return false;
	else return true;
}

bool FrameDifferenceRoute(Movement_Detect target)
{
	static int cloud_num = 1;
	for (auto row = target.frame_difference->begin(); row != target.frame_difference->end(); )
	{
		for (auto col = target.frame_one->begin(); col != target.frame_one->end(); col++)
		{
			if ((abs((*row).x - (*col).x) <= 0.1)
				&& (abs((*row).y - (*col).y) <= 0.1)
				&& (abs((*row).z - (*col).z) <= 0.1))
			{
				//cout << cloud_num << "point1 " << (*row).x << " " << (*row).y << " " << (*row).z
				//	<< " point2 " << (*col).x << " " << (*col).y << " " << (*col).z << endl;
				//cout << "minus" << (*row).x - (*col).x << " " << (*row).y - (*col).y << " " << (*row).z - (*col).z << endl;
				row = target.frame_difference->erase(row);
				//	col = frame_one->erase(col);
				break;
			}
			//else if (col != frame_one->end() - 1) ++col;
			else if (col == target.frame_one->end() - 1) ++row;
		}
	}

	string file_name = ("./result/difference" + to_string(cloud_num)) + ".txt";
	ofstream target_file(file_name);
	//cout << file_name << endl;
	for (auto it : (*(target.frame_difference)))
	{
		target_file << (it).x << " " << (it).y << " "
			<< (it).z << " " << (it).intensity << endl;
	}
	target_file.close();

	/*
	////////////
	search::KdTree<PointXYZI>::Ptr tree(new search::KdTree<PointXYZI>);
	tree->setInputCloud(target.frame_difference);
	//被分割出来的点云团（标号队列）
	vector<PointIndices> cluster_indices;
	//欧式分割器
	EuclideanClusterExtraction<PointXYZI> ec;
	ec.setClusterTolerance(0.35); // 2cm
	ec.setMinClusterSize(6);
	ec.setMaxClusterSize(50);
	//搜索策略树
	ec.setSearchMethod(tree);
	ec.setInputCloud(target.frame_difference);
	ec.extract(cluster_indices);
	int j = 0;
	pcl::PCDWriter writer;
	for (auto it = cluster_indices.begin(); it != cluster_indices.end(); it++)
	{
		PointCloud<PointXYZI>::Ptr cloud_cluster(new PointCloud<PointXYZI>);
		for (auto point = it->indices.begin(); point != it->indices.end(); point++)
			cloud_cluster->points.push_back(target.frame_difference->points[*point]); //*
		cloud_cluster->width = cloud_cluster->points.size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;
		std::stringstream ss;
		ss << "./result/class/" + to_string(cloud_num) + "cloud_cluster_" << j << ".pcd";
		writer.write<pcl::PointXYZI>(ss.str(), *cloud_cluster, false); //*
		++j;
		//cout << j << endl;
	}
	////////////
	*/

	cloud_num++;
	//if(target.gaussian_fliter()) cout << target.frame_difference->size() << endl;
	//return target.frame_difference;
	if (0 == target.frame_difference->size()) return false;
	else return true;
}