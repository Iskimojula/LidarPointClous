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
 * @brief 主要功能模块，用于调度其它算法模块
 */
class LiderLabelProcess
{
public:
	LiderLabelProcess() {};
	~LiderLabelProcess() {};
	/*旧版，现在不使用*/
	typedef void (CFilterHandler::*FilterFuncHandlePtr) (pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	typedef void (CSegHandler::*SegFuncHandlerPtr) (pcl::PointCloud<pcl::PointXYZI>::Ptr cloudsptr);
	/*旧版，现在不使用*/
public:

/*
 * @brief 模块路径初始化，用于初始化输出文件路径
 */
	void Init();

/*
* @brief 主函数
*/
	void Process();

/*
* @brief 清除lidardatacenter,ussdatacenter
*/
	void Clear();
private:
	/*旧版调试代码，现在不使用*/
	void AddFilter(FilterFuncHandlePtr fun);
	void AddSeg(SegFuncHandlerPtr fun);
	void Filterprocess();
	void Segprocess();
	void Viewer(std::string);
	void Freespace();
	void Freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr cloud);
	/*旧版调试代码，现在不使用*/

/*
* @brief m_dataptr指向的激光点云按照z轴可视化
*/
	void Viewer();

/*
* @brief 计算点云m_dataptr的x,y,z方向的最大值和最小值
*/
	void CalcPointSize();

/*
* @brief 将点云数据写入map.csv
*/
	void Savemap();

/*
* @brief 计算点云m_dataptr的某个方向的最小，最大值
* @param ptr指向激光点云的指针
* @label 要计算的方向，x,y,x
* @return label方向的最小值（first）、最小值（second）
*/
	std::pair<float, float> CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label = "x");

/*
* @brief 判断激光点云地图 map.csv是否存在
* @return true 地图存在，false 地图不存在
*/
	bool mapexist();
private:

/*
* @brief 各功能模块实例化
*/
	FileProcess fileprocess;
	BevProcess  bevprocess;

	CFilterHandler filterhandler;
	CSegHandler    seghandler;
	CFeaturehandler featurehandler;

	CPclViewer pclviewer;

	/*旧版调试代码，现在不使用*/
	std::vector<FilterFuncHandlePtr> filter ;
	std::vector<SegFuncHandlerPtr>   seg;
	/*旧版调试代码，现在不使用*/

/*
* @brief 成员变量，指向lidardatacenter中激光点云m_cloud的share_ptr
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr m_dataptr;

/*
* @brief 欧拉聚类后的激光点云m_cluster_indices索引的指针
*/
	boost::shared_ptr<std::vector<pcl::PointIndices>> m_clusterptr;

	/*旧版调试代码，现在不使用*/
	pcl::PointCloud<pcl::PointXYZ> m_lidar_freespace;
	/*旧版调试代码，现在不使用*/

/*
* @brief m_dataptr指向的激光点云数据的边界值
*/
	float m_minx;//x方向最小值
	float m_miny;//y方向最小值
	float m_minz;//z方向最小值
	float m_maxx;//x方向最大值
	float m_maxy;//y方向最大值
	float m_maxz;//z方向最大值


};