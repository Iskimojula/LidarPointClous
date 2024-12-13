#pragma once
#include "lidardatacenter.h"
#include "ussdatacenter.h"
#include "config.h"
#include "filterhandler.h"
#include "seghandler.h"
#include "featurehandler.h"
#include "bevprocess.h"
#include "pcl_viewer.h"
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common.h>
#include <pcl/common/time.h>
/*
 * @brief ��Ҫ����ģ�飬���ڵ��������㷨ģ��
 */
class LiderLabelProcess
{
public:
	LiderLabelProcess() {};
	~LiderLabelProcess() {};
	/*�ɰ棬���ڲ�ʹ��*/
	typedef void (CFilterHandler::*FilterFuncHandlePtr) (pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	typedef void (CSegHandler::*SegFuncHandlerPtr) (pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	/*�ɰ棬���ڲ�ʹ��*/
public:

/*
 * @brief ģ��·����ʼ�������ڳ�ʼ������ļ�·��
 */
	void Init();

/*
* @brief ������
*/
	void Process();

/*
* @brief ���lidardatacenter,ussdatacenter
*/
	void Clear();
private:
	/*�ɰ���Դ��룬���ڲ�ʹ��*/
	void AddFilter(FilterFuncHandlePtr fun);
	void AddSeg(SegFuncHandlerPtr fun);
	void Filterprocess();
	void Segprocess();
	void Viewer(std::string);
	void Freespace();
	void Freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloud);
	/*�ɰ���Դ��룬���ڲ�ʹ��*/

/*
* @brief m_dataptrָ��ļ�����ư���z����ӻ�
*/
	void Viewer();

/*
* @brief �������m_dataptr��x,y,z��������ֵ����Сֵ
*/
	void CalcPointSize();

/*
* @brief ����������д��map.csv
*/
	void Savemap();

/*
* @brief �������m_dataptr��ĳ���������С�����ֵ
* @param ptrָ�򼤹���Ƶ�ָ��
* @label Ҫ����ķ���x,y,x
* @return label�������Сֵ��first������Сֵ��second��
*/
	std::pair<float, float> CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label = "x");

/*
* @brief �жϼ�����Ƶ�ͼ map.csv�Ƿ����
* @return true ��ͼ���ڣ�false ��ͼ������
*/
	bool mapexist();
private:

/*
* @brief ������ģ��ʵ����
*/
	FileProcess fileprocess;
	BevProcess  bevprocess;

	CFilterHandler filterhandler;
	CSegHandler    seghandler;
	CFeaturehandler featurehandler;

	CPclViewer pclviewer;

	/*�ɰ���Դ��룬���ڲ�ʹ��*/
	std::vector<FilterFuncHandlePtr> filter ;
	std::vector<SegFuncHandlerPtr>   seg;
	/*�ɰ���Դ��룬���ڲ�ʹ��*/

/*
* @brief ��Ա������ָ��lidardatacenter�м������m_cloud��share_ptr
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr m_dataptr;

/*
* @brief ŷ�������ļ������m_cluster_indices������ָ��
*/
	boost::shared_ptr<std::vector<pcl::PointIndices>> m_clusterptr;

	/*�ɰ���Դ��룬���ڲ�ʹ��*/
	pcl::PointCloud<pcl::PointXYZ> m_lidar_freespace;
	/*�ɰ���Դ��룬���ڲ�ʹ��*/

/*
* @brief m_dataptrָ��ļ���������ݵı߽�ֵ
*/
	float m_minx;//x������Сֵ
	float m_miny;//y������Сֵ
	float m_minz;//z������Сֵ
	float m_maxx;//x�������ֵ
	float m_maxy;//y�������ֵ
	float m_maxz;//z�������ֵ


};