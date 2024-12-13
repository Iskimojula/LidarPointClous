#pragma once
#include <pcl/visualization/pcl_visualizer.h>
#include "cppheader.h"
#include "polygon.h"
#include "vehoutline.h"
#include "ultrasound_header.h"
/*
 * @brief debug功能，用于点云可视化
 *
 */
class CPclViewer
{
public:
	CPclViewer() {};
	~CPclViewer() {};

public:
	void lidarcloudmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds);
	void bevinmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds, pcl::PointCloud<pcl::PointXYZI>::Ptr vehoutline, pcl::PointCloud<pcl::PointXYZI>::Ptr &bevrange);
	void bevinmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds, tObjProperty3D &vehpose);
public:
	//m_vehicle_outline_V

};





