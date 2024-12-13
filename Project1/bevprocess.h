#pragma once
#include "seghandler.h"
#include <opencv2/opencv.hpp>
#include "imgconvert.h"
/*
 * @brief 根据激光点云boundary（自车坐标）生成gt图
 * 
 */
class BevProcess
{
public:

	BevProcess() {};

/*
 * @brief 构造函数，用于创建一个BevProcess对象
 * @param ptr 指向自车坐标中激光点云boundary的指针
 */
	BevProcess(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr) { SetLidarFreespace(ptr); };

	~BevProcess() {};

/*
* @brief 主函数，根据自车坐标下的激光点云boundary生成gt图（.png）
* @param 
*/
	int Process();

/*
* @brief 给成员变量m_bdy赋值
* @param ptr 指向包含自车坐标下激光雷达boundary数据的指针
*/
	void SetLidarFreespace(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr);

/*
* @brief 给成员变量m_ts赋值
* @param ts 当前标注的超声数据的时间戳
*/
	void SetUssTimestamp(TimestampType & ts);

/*
* @brief 输出一个指向成员变量m_ts_trajectory的指针
* @return 输出一个指向成员变量m_ts_trajectory的shared_ptr
*/
	boost::shared_ptr<std::vector<TimestampType>> GetLabelUssTs();
/*
* @brief  输出成员变量m_size
* @return 成员变量m_size
*/
	int & GetLabelSize();
private:
/*
* @brief 私有成员变量，指向自车坐标中激光点云boundary的指针
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr m_bdy;

/*
* @brief 私有成员变量，以cv::Mat格式存储的gt图
*/
	cv::Mat m_bev_image;

/*
* @brief 私有成员变量，gt图对应的时间戳
*/
	TimestampType m_ts;

/*
* @brief 私有成员变量，已经标注的gt图数量
*/
	int m_size = 0; 
/*
* @brief 私有成员变量，vector用于放已经标注的超声数据对应的时间戳
*/
	std::vector<TimestampType> m_ts_trajectory;
};


