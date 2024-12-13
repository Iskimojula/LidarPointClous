#include "filterhandler.h"

void CFilterHandler::valuefilterX(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::PassThrough<pcl::PointXYZI> pass;
	pass.setInputCloud(cloudsptr);
	pass.setFilterFieldName("x");
	pass.setFilterLimits(RANGEX_MIN, RANGEX_MAX);
	pass.filter(*cloudsptr);
}

void CFilterHandler::valuefilterY(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::PassThrough<pcl::PointXYZI> pass;
	pass.setInputCloud(cloudsptr);
	pass.setFilterFieldName("y");
	pass.setFilterLimits(RANGEY_MIN, RANGEY_MAX);
	pass.filter(*cloudsptr);


}

void CFilterHandler::valuefilterZ(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::PassThrough<pcl::PointXYZI> pass;
	pass.setInputCloud(cloudsptr);
	pass.setFilterFieldName("z");
	pass.setFilterLimits(RANGEZ_MIN, RANGEZ_MAX);
	pass.filter(*cloudsptr);
}

void CFilterHandler::volexgridfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::VoxelGrid<pcl::PointXYZI> voxel;
	voxel.setInputCloud(cloudsptr);
	voxel.setLeafSize(VOXELESFSIZE, VOXELESFSIZE, VOXELESFSIZE);
	voxel.filter(*cloudsptr);

}

void CFilterHandler::octreevolexgridfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
#if 1
	pcl::octree::OctreePointCloud<pcl::PointXYZI> octree(VOXELESFSIZE);
	octree.setInputCloud(cloudsptr);
	octree.addPointsFromInputCloud();
	std::vector<pcl::PointXYZI,AlignedPointT> voxel_centers;
	octree.getOccupiedVoxelCenters(voxel_centers);

	cloudsptr->clear();

	cloudsptr->width = voxel_centers.size();
	cloudsptr->height = 1;
	cloudsptr->points.resize(cloudsptr->height * cloudsptr->width );

	for (size_t i = 0; i < voxel_centers.size() - 1; i++)
	{
		cloudsptr->points[i].x = voxel_centers[i].x;
		cloudsptr->points[i].y = voxel_centers[i].y;
		cloudsptr->points[i].z = voxel_centers[i].z;
	}
#endif



}

void CFilterHandler::projectionfilter(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr)
{
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
	coefficients->values.resize(4);
	coefficients->values[0] = 0.0f;
	coefficients->values[1] = 0.0f;
	coefficients->values[2] = 1.0f;
	coefficients->values[3] = 0.0f;

	pcl::ProjectInliers<pcl::PointXYZI> proj;
	proj.setModelType(pcl::SACMODEL_PLANE);
	proj.setInputCloud(cloudsptr);
	proj.setModelCoefficients(coefficients);
	proj.filter(*cloudsptr);

}

pcl::PointCloud<pcl::PointXYZI>::Ptr  CFilterHandler::polygonfilter(const pcl::PointCloud<pcl::PointXYZI>::Ptr src_cloudsptr,  CPolygon & polygon )
{
	static pcl::PointCloud<pcl::PointXYZI> bevclouds;
	bevclouds.clear();

	for (int i = 0; i < src_cloudsptr->size(); i++)
	{
		if (polygon.Inside(src_cloudsptr->points[i].x, src_cloudsptr->points[i].y))
		{
			bevclouds.push_back(src_cloudsptr->points[i]);
		}
	}

	return boost::make_shared<pcl::PointCloud<pcl::PointXYZI>>(bevclouds);
}


