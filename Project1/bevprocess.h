#pragma once
#include "seghandler.h"
#include <opencv2/opencv.hpp>
#include "imgconvert.h"
/*
 * @brief ���ݼ������boundary���Գ����꣩����gtͼ
 * 
 */
class BevProcess
{
public:

	BevProcess() {};

/*
 * @brief ���캯�������ڴ���һ��BevProcess����
 * @param ptr ָ���Գ������м������boundary��ָ��
 */
	BevProcess(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr) { SetLidarFreespace(ptr); };

	~BevProcess() {};

/*
* @brief �������������Գ������µļ������boundary����gtͼ��.png��
* @param 
*/
	int Process();

/*
* @brief ����Ա����m_bdy��ֵ
* @param ptr ָ������Գ������¼����״�boundary���ݵ�ָ��
*/
	void SetLidarFreespace(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr);

/*
* @brief ����Ա����m_ts��ֵ
* @param ts ��ǰ��ע�ĳ������ݵ�ʱ���
*/
	void SetUssTimestamp(TimestampType & ts);

/*
* @brief ���һ��ָ���Ա����m_ts_trajectory��ָ��
* @return ���һ��ָ���Ա����m_ts_trajectory��shared_ptr
*/
	boost::shared_ptr<std::vector<TimestampType>> GetLabelUssTs();
/*
* @brief  �����Ա����m_size
* @return ��Ա����m_size
*/
	int & GetLabelSize();
private:
/*
* @brief ˽�г�Ա������ָ���Գ������м������boundary��ָ��
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr m_bdy;

/*
* @brief ˽�г�Ա��������cv::Mat��ʽ�洢��gtͼ
*/
	cv::Mat m_bev_image;

/*
* @brief ˽�г�Ա������gtͼ��Ӧ��ʱ���
*/
	TimestampType m_ts;

/*
* @brief ˽�г�Ա�������Ѿ���ע��gtͼ����
*/
	int m_size = 0; 
/*
* @brief ˽�г�Ա������vector���ڷ��Ѿ���ע�ĳ������ݶ�Ӧ��ʱ���
*/
	std::vector<TimestampType> m_ts_trajectory;
};


