#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include "poconvert.h"
#include "config.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
typedef std::vector<TPoint> Tfreespace;

class CFeaturehandler
{
public:
	CFeaturehandler() {};
	~CFeaturehandler() {};
	
	//获取激光点云boundary,点云为全局坐标
	pcl::PointCloud<pcl::PointXYZI> & freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_w,const TPose vehpose);

	//获取激光点云boundary,点云为自车坐标
	pcl::PointCloud<pcl::PointXYZI> & freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_v);
	
	//获取点云的边界值
	std::pair<float, float> CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label = "x");

private:

};
