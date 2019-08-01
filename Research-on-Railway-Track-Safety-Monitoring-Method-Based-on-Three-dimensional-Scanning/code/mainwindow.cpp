#include "mainwindow.h"
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    //view(new QGraphicsView(scene, this)),
	cloud(new PointCloud<PointXYZRGB>)
{
    //setCentralWidget(view);
    resize(1200, 600);
    setWindowTitle(QStringLiteral("三维铁路安全监控系统"));
    initScene();
	
	//splitter = new QSplitter;

	viewer_main = new PointCloudViewer(parent);
	//splitter->addWidget(viewer_main->getWidget());
	//setCentralWidget(splitter);
	setCentralWidget(viewer_main->getWidget());
	//viewer2 = new PointCloudViewer(parent);
	//splitter->addWidget(viewer2->getWidget());
	//splitter->addWidget(viewer3->getwidget());
	
	//setCentralWidget(parent);
    //initSceneBackground();
	//Pcl_Viewer *view = new Pcl_Viewer(this);
	//view->PclViewerShow();
	
	//vtkSmartPointer<vtkWin32OutputWindow> outputWindow = vtkSmartPointer<vtkWin32OutputWindow>::New();
	//outputWindow->SetSendToStdErr(true);
	//vtkOutputWindow::SetInstance(outputWindow);
	//vtkOutputWindow->SetGlobalWarningDisplay(0);
	//vtkOutputWindow *w = vtkOutputWindow::GetInstance();
	//vtkOutputWindow::GetInstance()->DisplayText(" ");
	//vtkOutputWindow::GetInstance()->Delete();
	//w->GlobalWarningDisplayOff();
	//w->SetGlobalWarningDisplay(0);
	//w->Delete();
	//w->FastDelete();
	
	//setCentralWidget(qvtkWidget);

	//qvtkWidget->update();

	number = new LCDNumber();
	alarm = new LCDAlarm();
	//point_cloud = new Point_Cloud_Start();
	//point_cloud_main = new PointCloudMain();
	point_cloud_main = new PointCloudMain(viewer_main);
	//connect(point_cloud, SIGNAL(filename), qlcd, SLOT(Display));
	this->connect(point_cloud_main, &PointCloudMain::FileNum, number, &LCDNumber::displayNumber);

	QHBoxLayout* layout_left = new QHBoxLayout();//水平布局
	//QHBoxLayout* layout_right = new QHBoxLayout();//水平布局
	connect(point_cloud_main, &PointCloudMain::SafeFlag, alarm, &LCDAlarm::displaySafe);
	connect(point_cloud_main, &PointCloudMain::WarnFlag, alarm, &LCDAlarm::displayWarn);
	layout_left->addWidget(number->getNumber(), 0, Qt::AlignLeft | Qt::AlignTop);
	//layout_right->addWidget(alarm->getAlarm(), 0, Qt::AlignRight | Qt::AlignTop);
	layout_left->addWidget(alarm->getAlarm(), 0, Qt::AlignRight | Qt::AlignTop);
	viewer_main->getWidget()->setLayout(layout_left);
	//viewer_main->getWidget()->setLayout(layout_right);
	//viewer2->getWidget()->setLayout(layout_right);
	//this->setLayout(layout);

    QMenu *detect = menuBar()->addMenu(QStringLiteral("监测"));
	toolBar = addToolBar(QStringLiteral("监测"));
	start_button = new StartDetect(this, point_cloud_main, detect, toolBar);
	pause_button = new PauseDetect(this, point_cloud_main, detect, toolBar);
	keep_button = new KeepDetect(this, point_cloud_main, detect, toolBar);

	QMenu *file = menuBar()->addMenu(QStringLiteral("文件"));
	toolBar = addToolBar(QStringLiteral("文件"));
	open_button = new OpenPointFile(this, file, toolBar);
	save_button = new SavePointFile(this, file, toolBar);

	QMenu *set = menuBar()->addMenu(QStringLiteral("设置"));
	toolBar = addToolBar(QStringLiteral("设置"));
	differ_button = new ShowDifferPoint(this, point_cloud_main, set, toolBar);
	cluster_button = new ShowClusterPoint(this, point_cloud_main, set, toolBar);
	reset_button = new ResetView(this, point_cloud_main, set, toolBar);

	connect(open_button->getButton(), &QAction::triggered, this, &MainWindow::openFile);
	connect(save_button->getButton(), &QAction::triggered, this, &MainWindow::saveFile);
	connect(viewer_main, &PointCloudViewer::ViewShowOver, 
		point_cloud_main, &PointCloudMain::keepShow, Qt::DirectConnection);
	//connect(point_cloud_main, &PointCloudMain::NewViewer,
	//	viewer_main, &PointCloudViewer::updatePointCloud, Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::green));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::openFile()
{
	static int click_flag = 1;
	//viewer->set
	//wglMakeCurrent(NULL, NULL);
	//viewer3 = new Pcl_Viewer(this);
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open PointCloud"), ".",
		tr("Open PCD files(*.pcd)"));

	if (1 == click_flag)
	{
		viewer = new pcl::visualization::PCLVisualizer("查看点云文件");
		//viewer.reset(new pcl::visualization::PCLVisualizer("查看点云文件", false));
		//viewer = new pcl::visualization::PCLVisualizer("查看点云文件");
		//pcl::visualization::PCLVisualizer viewer("3D viewer");
		//viewer->initCameraParameters();
		if (!fileName.isEmpty())
		{
			string file_name = fileName.toStdString();
			if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(file_name, *cloud) == -1)
				PCL_ERROR("Couldn't read file pcd\n");
		}
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color(cloud, 255, 255, 255);
		viewer->addPointCloud<pcl::PointXYZRGB>(cloud, cloud_color, "cloud");
		click_flag++;
	}

	else if (2 == click_flag)
	{
		viewer->close();
		viewer = new pcl::visualization::PCLVisualizer("查看点云文件");
		//viewer->initCameraParameters();
		//viewer = new boost::shared_ptr<pcl::visualization::PCLVisualizer>;
		//viewer.reset(new pcl::visualization::PCLVisualizer("查看点云文件", false));
		//viewer = new pcl::visualization::PCLVisualizer("查看点云文件");
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color(cloud, 255, 255, 255);
		int viewport1(0);
		viewer->createViewPort(0.0, 0.0, 0.5, 1.0, viewport1);
		viewer->setBackgroundColor(0.0, 0.0, 0.0, viewport1);
		viewer->addText("Point Cloud 1", 10, 10, "viewport1", viewport1);
		viewer->addPointCloud<pcl::PointXYZRGB>(cloud, cloud_color, "cloud1", viewport1);

		if (!fileName.isEmpty())
		{
			string file_name = fileName.toStdString();
			if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(file_name, *cloud) == -1)
				PCL_ERROR("Couldn't read file pcd\n");
		}

		int viewport2(0);
		viewer->createViewPort(0.5, 0.0, 1.0, 1.0, viewport2);
		viewer->setBackgroundColor(0.3, 0.3, 0.3, viewport2);
		viewer->addText("Point Cloud 2", 10, 10, "viewport2", viewport2);
		//viewer->setBackgroundColor(0.0, 0.0, 0.0, viewport2);

		//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "viewport1");
		//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "viewport2");
		viewer->addCoordinateSystem(1.0);
		viewer->addPointCloud<pcl::PointXYZRGB>(cloud, cloud_color, "cloud2", viewport2);
		
		click_flag = 1;
	}
	
		//viewer1->PclViewerShow(cloud)
}
	
void MainWindow::saveFile()
{
	point_cloud_main->pauseDetect();
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save PointCloud"), ".",
		tr("Save PCD files(*.pcd)"));
	if (!fileName.isEmpty())
	{
		pcl::PointCloud<pcl::PointXYZRGB> &cloud = *(viewer_main->getPointCloud());
		//PointCloud<PointXYZRGBI>::Ptr cloud;//(new PointCloud<PointXYZRGBI>);
		//pcl::io::savePCDFileASCII(fileName.toStdString(), viewer2->getpoint());
		pcl::io::savePCDFileBinary(fileName.toStdString(), cloud);
	}
	point_cloud_main->keepDetect();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	QMessageBox button(QMessageBox::Warning, QStringLiteral("提示"), QStringLiteral("确认退出程序？"));
	button.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	button.setButtonText(QMessageBox::Yes, QStringLiteral("结束"));
	button.setButtonText(QMessageBox::No, QStringLiteral("返回"));

	if (button.exec() != QMessageBox::Yes)
	{
		event->ignore();
	}
	else
	{
		point_cloud_main->pauseDetect();
		this->close();
	}
}
