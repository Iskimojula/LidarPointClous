#pragma once
#define BOOST_TYPEOF_EMULATION
#include "cppheader.h"
#include "config.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/octree/octree.h>
#include <boost/thread/thread.hpp>
#include "polygon.h"

class CFilterHandler
{
public :
	CFilterHandler() {};
	~CFilterHandler() {};

	typedef Eigen::aligned_allocator<pcl::PointXYZI> AlignedPointT;

public :
	//直通滤波
	void valuefilterX(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	void valuefilterY(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	void valuefilterZ(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	
	//体素滤波
	void volexgridfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);

	//基于八叉树的体素滤波
	void octreevolexgridfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);

	//XY 平面投影
	void projectionfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);

	//XY 平面多边形滤波
	pcl::PointCloud<pcl::PointXYZI>::Ptr polygonfilter(const pcl::PointCloud<pcl::PointXYZI>::Ptr src_cloudsptr, CPolygon & polygon);
};
