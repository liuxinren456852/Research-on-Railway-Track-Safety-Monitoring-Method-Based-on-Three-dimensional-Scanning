#include "pch.h"
#include "viewer.h"
#include <mutex>
#include <boost/thread/shared_mutex.hpp>

PointCloudViewer::PointCloudViewer(QWidget *window) : QTVK_widget(new QVTKWidget(window))
	//foreground(new pcl::PointCloud<pcl::PointXYZRGB>)
{
	//vtkObject::GlobalWarningDisplayOff();
	//QTVK_widget->vtkObject::GlobalWarningDisplayOff();
	//QVTK_widget = new QVTK_widget(window);
	//QTVK_widget->setStyleSheet(QString::fromUtf8("border:1px solid white"));
	//setFormat(const QSurfaceFormat &format)

	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	viewer->setBackgroundColor(0, 0, 0);
	//viewer->setBackgroundColor(142, 229, 238);
	//viewer = new pcl::visualization::PCLVisualizer("");
	//background.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
	//qvtkWidget = new QVTKWidget(window);
	//QVTK_widget->setMinimumSize(100, 300);
	QTVK_widget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(QTVK_widget->GetInteractor(), QTVK_widget->GetRenderWindow());
	//setCentralWidget(QVTK_widget);
	//viewer->addPointCloud<pcl::PointXYZRGB>(background, "cloud");
	//pcl::io::loadPCDFile<pcl::PointXYZRGB>("D:\\123.pcd", *foreground);
	//foreground->resize(300);
	//int vp;
	background.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
	foreground.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
	//viewer->createViewPort(0.0, 0.0, 1.0, 1.0, vp);
	viewer->addPointCloud(background, "background");
	viewer->addPointCloud(foreground, "foreground");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "foreground");
	//viewer->resetCamera();
	viewer->addCoordinateSystem(3);
	QTVK_widget->update();
}

PointCloudViewer::PointCloudViewer(QWidget *window, PointCloud<PointXYZRGB>::Ptr & result) : background(result)
{
	QTVK_widget = new QVTKWidget(window);
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));

	viewer->addPointCloud<pcl::PointXYZRGB>(background, "background");
	//qvtkWidget = new QVTKWidget(window);
	//QVTK_widget->setMinimumSize(100, 300);
	QTVK_widget->SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(QTVK_widget->GetInteractor(), QTVK_widget->GetRenderWindow());
	viewer->setBackgroundColor(0, 0, 0);
	//setCentralWidget(QVTK_widget);
	QTVK_widget->update();
}

bool PointCloudViewer::showPointCloud()
{
	wglMakeCurrent(NULL, NULL);
	viewer->updatePointCloud<pcl::PointXYZRGB>(background, "background");
	//viewer->spin();
	viewer->resetCamera();
	QTVK_widget->update();
	return true;
}

/*
bool PointCloudViewer::showPointCloud(PointCloud<PointXYZRGB>::Ptr point)
{
	wglMakeCurrent(NULL, NULL);
	background = point;
	//viewer->spin();
	//QVTK_widget->update();
	//viewer->resetCamera();
	//viewer->addPointCloud<pcl::PointXYZRGB>(background, "cloud");
	viewer->updatePointCloud<pcl::PointXYZRGB>(background, "background");
	viewer->resetCamera();
	QTVK_widget->update();
	return true;
}
*/

bool PointCloudViewer::showPointCloud(const PointCloud<PointXYZRGB>::Ptr &point_cloud_origin, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ)
{
	//boost::mutex mutex;
	//boost::unique_lock<boost::mutex> lock(mutex);
	//qDebug() << background->size() << endl;
	//qDebug() << "show^^^^^^^^^^^^^^^^^^" << endl;
	//qDebug() << point_cloud_actual->size() << endl;
	wglMakeCurrent(NULL, NULL);
	//if(background->empty())background = point_cloud_actual;
	//background = point_cloud_actual;
	if (background->empty()) background = point_cloud_origin;
	foreground = point_cloud_differ;

	//background = background_tem.makeShared();
	//foreground = foreground_tem.makeShared();

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> point_color(foreground, 255, 0, 0);
	//viewer->updatePointCloud<pcl::PointXYZRGB>(point_cloud_actual, "background");
	//viewer->updatePointCloud<pcl::PointXYZRGB>(point_cloud_differ, point_color, "foreground");
	viewer->updatePointCloud<pcl::PointXYZRGB>(background, "background");
	viewer->updatePointCloud<pcl::PointXYZRGB>(foreground, point_color, "foreground");
	//else viewer->removePointCloud("foreground");
	//viewer->spin();
	//viewer->updateCamera();
	//Sleep(1);
	//QTVK_widget->update();
	//return true;
	QTVK_widget->update();
	//qDebug() << point_cloud_actual->size() << endl;
	showView();
	return true;
}

void PointCloudViewer::updatePointCloud(const PointCloud<PointXYZRGB>::Ptr &point_cloud_actual, const PointCloud<PointXYZRGB>::Ptr &point_cloud_differ)
{
	//qDebug() << "show^^^^^^^^^^^^^^^^^^" << endl;
	//qDebug() << point_cloud_actual->size() << endl;
	wglMakeCurrent(NULL, NULL);
	background = point_cloud_actual;
	foreground = point_cloud_differ;

	//background = background_tem.makeShared();
	//foreground = foreground_tem.makeShared();

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> point_color(point_cloud_actual, 255, 0, 0);
	viewer->updatePointCloud<pcl::PointXYZRGB>(point_cloud_actual, "background");
	viewer->updatePointCloud<pcl::PointXYZRGB>(point_cloud_differ, point_color, "foreground");
	//else viewer->removePointCloud("foreground");
	//viewer->spin();
	//viewer->updateCamera();
	//QTVK_widget->update();
	QTVK_widget->update();
	//QTVK_widget->update();
	//return true;
}


QVTKWidget * PointCloudViewer::getWidget()
{
	return QTVK_widget;
}

PointCloud<PointXYZRGB>::Ptr PointCloudViewer::getPointCloud()
{
	return foreground;
}

void PointCloudViewer::resetView()
{
	//Eigen::Affine3fgetViewerPose();
	//viewer->setCameraPosition(0, 0 ,0 , 0, 0, 0);
	viewer->resetCamera();
}
