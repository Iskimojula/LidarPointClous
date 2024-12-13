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
	
	//��ȡ�������boundary,����Ϊȫ������
	pcl::PointCloud<pcl::PointXYZI> & freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_w,const TPose vehpose);

	//��ȡ�������boundary,����Ϊ�Գ�����
	pcl::PointCloud<pcl::PointXYZI> & freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr_v);
	
	//��ȡ���Ƶı߽�ֵ
	std::pair<float, float> CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label = "x");

private:

};
