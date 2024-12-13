#include "seghandler.h"

void CSegHandler::planeseg(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	// 创建分割器
	pcl::SACSegmentation<pcl::PointXYZI> seg;
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setMaxIterations(1000);
	seg.setDistanceThreshold(0.05);

	// 创建容器存储地面点和非地面点
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);

	// 分割地面
	seg.setInputCloud(cloudsptr);
	seg.segment(*inliers, *coefficients);

	// 创建一个新的点云存储非地面点
	pcl::ExtractIndices<pcl::PointXYZI> extract;
	extract.setInputCloud(cloudsptr);
	extract.setIndices(inliers);
	extract.setNegative(true);
	extract.filter(*cloudsptr);

	// cloud_filtered 中存储了去除地面后的点云
}

void CSegHandler::clusterseg(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::search::KdTree<pcl::PointXYZI>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZI>);
	tree->setInputCloud(cloudsptr);

	pcl::EuclideanClusterExtraction<pcl::PointXYZI> ec;
	ec.setClusterTolerance(EULERDIS);
	ec.setMinClusterSize(MINCLUSTERDIS);
	ec.setSearchMethod(tree);
	ec.setInputCloud(cloudsptr);
	ec.extract(m_cluster_indices);
}

boost::shared_ptr<std::vector<pcl::PointIndices>> CSegHandler::getclusterindices()
{
	return boost::make_shared<std::vector<pcl::PointIndices>>(m_cluster_indices);
}
