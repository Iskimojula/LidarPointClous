#pragma once
#include "cppheader.h"
#include "config.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
class CSegHandler
{
public:
	CSegHandler() {};
	~CSegHandler() {};

public:

	//基于RANSAC的地面分割
	void planeseg(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);

	//基于欧式距离分割
	void clusterseg(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);

	boost::shared_ptr<std::vector<pcl::PointIndices>> getclusterindices();

private:

/*
* @brief 欧拉聚类后的激光点云boundary cluster
*/
	std::vector<pcl::PointIndices> m_cluster_indices;


};
