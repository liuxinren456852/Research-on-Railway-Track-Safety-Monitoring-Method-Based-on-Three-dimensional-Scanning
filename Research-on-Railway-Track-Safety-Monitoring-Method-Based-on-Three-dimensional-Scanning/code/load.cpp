#include "pch.h"
#include "load.h"
#include <QDebug>

/*
struct _finddata_t {
 unsigned attrib;
 time_t time_create;
 time_t time_access;
 time_t time_write;
 _fsize_t size;
 char name[260];
};
unsigned atrrib： 文件属性的存储位置。它存储一个unsigned单元，
	用于表示文件的属性。文件属性是用位表示的，主要有以下一些：
	_A_ARCH（存档）、 _A_HIDDEN（隐藏）、_A_NORMAL（正常）、
	_A_RDONLY（只读）、_A_SUBDIR（文件夹）、_A_SYSTEM（系统）。
	这些都是在中定义的宏，可以直接使用，而本身的意义其实是一
	个无符号整型（只不过这个整型应该是2的几次幂，从而保证只有
	一位为 1，而其他位为0）。既然是位表示，那么当一个文件有多
	个属性时，它往往是通过位或的方式，来得到几个属性的综合。
	例如只读+隐藏+系统属性，应该为：_A_HIDDEN | _A_RDONLY |
	_A_SYSTEM 。
time_t time_create： 文件创建时间。
time_t time_access： 文件最后一次被访问的时间。
time_t time_write： 文件最后一次被修改的时间。
_fsize_t size： 文件的大小。
char name [_MAX_FNAME ]：文件的文件名。这里的_MAX_FNAME是一个
	常量宏，它在头文件中被定义，表示的是文件名的最大长度。

1、_findfirst函数：long _findfirst(const char *, struct _finddata_t *);
	第一个参数为文件名，可以用"*.*"来查找所有文件，也可以用"*.cpp"来查
	找.cpp文件。第二个参数是_finddata_t结构体指针。若查找成功，返回文
	件句柄，若失败，返回-1。
2、_findnext函数：int _findnext(long, struct _finddata_t *);
	第一个参数为文件句柄，第二个参数同样为_finddata_t结构体指针。若查找
	成功，返回0，失败返回-1。
3、_findclose()函数：int _findclose(long);
	只有一个参数，文件句柄。若关闭成功返回0，失败返回-1。
*/

PointCloudFile::PointCloudFile():in_path("D:\\2.预警") {}
//PointCloudFile::PointCloudFile() :in_path("C:\\Users\\mi\\OneDrive - mail.scut.edu.cn\\桌面\\错误") {}
PointCloudFile::PointCloudFile(string file_path) :in_path(file_path) {}

//重载比较函数，修改为按文件的创建时间排列，模拟点云序列的生成过程
bool comp(const _finddata_t &a, const _finddata_t &b) {
	return a.time_create < b.time_create;
}

//private函数，用于文件列表加载
bool PointCloudFile::getPointCloud()
{
	curr = in_path + "\\*.pcd";
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1L) //若不存在指定扩展名文件
	{
		cout << "没有找到匹配文件!" << endl;
		return false;
	}
	else
	{
		point_cloud_file.push_back(fileinfo); //存入第一个文件
		while (!(_findnext(handle, &fileinfo)))
		{
			point_cloud_file.push_back(fileinfo);
		}
		_findclose(handle);
	}
	//按文件创建顺序排列后，讲文件名按顺序push到point_cloud_name
	sort(point_cloud_file.begin(), point_cloud_file.end(), comp);
	for (auto it = point_cloud_file.begin(); it != point_cloud_file.end(); it++)
	{
		//qDebug() << (*it).name << endl;
		point_cloud_name.push_back((*it).name);
	}
	return true;
}

//public函数，用于返回文件名称列表
vector<string> PointCloudFile::getPointCloudName()
{
	if (getPointCloud()) return point_cloud_name;
}

PointCloud<PointXYZRGB>::Ptr loadPointCloud(PointCloudFile target)
{
	PointCloud<PointXYZRGB>::Ptr point_cloud(new PointCloud<PointXYZRGB>);
	//static int point_cloud_num = 0; //记录读取到了第几个点云文件
	static int point_cloud_num = 0;
	string point_cloud_target_name = target.in_path + "\\" + target.point_cloud_name[point_cloud_num];
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(point_cloud_target_name, *point_cloud) == -1)
	{
		PCL_ERROR("Couldn't read file pcd\n");
	}
	point_cloud_num++;
	qDebug() << "num" << point_cloud_num << " load succeed!" << endl;
	
	//if (point_cloud_num % 10 == 0) point_cloud_num_th += 10;
	if (point_cloud_num == target.point_cloud_name.size()) point_cloud_num = 0;
	return point_cloud;
}

//string PointCloudFile::getFileName()
//{
	//return point_cloud_name[point_cloud_num];
//}