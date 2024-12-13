#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/make_shared.hpp>
#include <pcl/common/concatenate.h>
#include "fileprocess.h"
#include "lidarconvert.h"
#include "poconvert.h"
#include "seghandler.h"
/*
 * @brief ����ģʽ�����ڽ�������.bin�ļ�����ȡ�����ͼ��map.csv��,�洢�����������
 */
class LidardateCenter
{
public:
	LidardateCenter() {};
	~LidardateCenter() {};
	static LidardateCenter& Instance();
public:

/*
 * @brief ��ȡ�����ͼ��csv��ʽ�����������Ա����m_cloud
 * @param lidarpointclouds �����ͼ���ļ�·��
 * @param ��Ҫ������������Ĭ��Ϊ0
 */
	void ReadLidarPointClouds(const std::string lidarpointclouds, const int skipline = 0);

/*
* @brief ��ȡ����.binԭʼ���ݣ��������Ա����m_cloud
* @param lidarpointclouds ����.bin���ļ�·��
*/
	void ReadLidarPointClouds(align_lidar_pair lidarpointclouds);

/*
* @brief �������״�bin���ж��Ƿ���FOV��Χ���������ת�������ݴ��ڳ�Ա����m_cloud��
* @param label �󼤹�/�Ҽ���
* @param ����.bin���ݴ��·����ʱ���������pose
*/
	void readunilaterallidar(std::string label, LidarFileInfo &fileinfo);

/*
* @brief ���ָ�򼤹����m_cloud��ָ��
* @return ָ��m_cloude��ָ��
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr GetLidarClouds();

/*
* @brief ����������m_cloud
*/
	void Clear();
	
private:
/*
* @brief ���csv����
* @param str csv��ʽ����
* @return ָ��m_cloude��ָ��
*/
	std::vector<std::string> splitstring(const std::string &str);
/*
* @brief �ж��Գ������µļ������ݵ��Ƿ���LIDARXYFOV��LIDARZFOV��Χ��
* @param lidarpoint_v �Գ������µļ�������
* @return true:��fov��Χ�� false:����fov��Χ��
*/
	bool IsInFov(const PointT lidarpoint_v);
	
private:

	static LidardateCenter instance;
/*
* @brief ȫ������ϵ�µļ������
*/
	pcl::PointCloud<pcl::PointXYZI> m_cloud;
/*
* @brief convertʵ����
*/
	CLidarDataConvert lidarconvert;
	CPoDataConvert    poconvert;
	

};
