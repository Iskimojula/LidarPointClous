#include "featurehandler.h"

pcl::PointCloud<pcl::PointXYZI>  & CFeaturehandler::freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_w,TPose vehpose)
{

	pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_v(new pcl::PointCloud<pcl::PointXYZI>);
	CPoDataConvert poconvert;
	for (int i = 0; i < cloudsptr_w->size(); i++)
	{
		TPoint pointw = { cloudsptr_w->points[i].x,cloudsptr_w->points[i].y };
		TPoint pointv = poconvert.trans2V(pointw, vehpose);

		pcl::PointXYZI cloud_v;
		
		cloud_v.x = pointv.x;
		cloud_v.y = pointv.y;
		cloud_v.z = cloudsptr_w->points[i].z;
		cloud_v.intensity = cloudsptr_w->points[i].intensity;

		cloudsptr_v->push_back(cloud_v);
	}

	return freespace(cloudsptr_v);
}

pcl::PointCloud<pcl::PointXYZI>  & CFeaturehandler::freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_v)
{
	static pcl::PointCloud<pcl::PointXYZI> boundary_front;
	boundary_front.clear();
	std::pair<float, float> range_y = CalcPointSize(cloudsptr_v, "y");

	for (auto step = range_y.first; step <= range_y.second; step += PIXELSIZE)
	{
		pcl::PointCloud<pcl::PointXYZI>::Ptr slicer_cloud(new pcl::PointCloud<pcl::PointXYZI>);
		pcl::PassThrough<pcl::PointXYZI> pass;
		pass.setInputCloud(cloudsptr_v);
		pass.setFilterFieldName("y");
		pass.setFilterLimits(step, step + PIXELSIZE);
		pass.filter(*slicer_cloud);

		std::pair<float, float> range_x = CalcPointSize(slicer_cloud, "x");
		if (range_x.first <= BevGridEdgeX_Front_m && range_x.first > 0)
		{
			pcl::PointXYZI bnd;
			bnd.x = range_x.first;
			bnd.y = static_cast<float>((step + step + PIXELSIZE) / 2.0f);
			bnd.z = 0.0f;
			bnd.intensity = 0.0f;

			TPoint boundary = { range_x.first,static_cast<float>((step + step + PIXELSIZE) / 2.0f) };
			boundary_front.push_back(bnd);
		}

	}
	return boundary_front;
}

std::pair<float, float> CFeaturehandler::CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label)
{
	pcl::PointXYZI min_pt, max_pt;
	min_pt.x = min_pt.y = min_pt.z = std::numeric_limits<float>::max();
	max_pt.x = max_pt.y = max_pt.z = -std::numeric_limits<float>::max();

	for (size_t i = 0; i < ptr->points.size(); i++) {
		if (ptr->points[i].x < min_pt.x) min_pt.x = ptr->points[i].x;
		if (ptr->points[i].y < min_pt.y) min_pt.y = ptr->points[i].y;
		if (ptr->points[i].z < min_pt.z) min_pt.z = ptr->points[i].z;

		if (ptr->points[i].x > max_pt.x) max_pt.x = ptr->points[i].x;
		if (ptr->points[i].y > max_pt.y) max_pt.y = ptr->points[i].y;
		if (ptr->points[i].z > max_pt.z) max_pt.z = ptr->points[i].z;
	}

	if (label == "x")
	{
		return std::make_pair(min_pt.x, max_pt.x);
	}

	if (label == "y")
	{
		return std::make_pair(min_pt.y, max_pt.y);
	}

	if (label == "z")
	{
		return std::make_pair(min_pt.z, max_pt.z);
	}
}
