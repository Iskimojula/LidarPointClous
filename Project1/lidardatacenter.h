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
 * @brief 单例模式，用于解析激光.bin文件、读取激光地图（map.csv）,存储激光点云数据
 */
class LidardateCenter
{
public:
	LidardateCenter() {};
	~LidardateCenter() {};
	static LidardateCenter& Instance();
public:

/*
 * @brief 读取激光地图（csv格式），并放入成员变量m_cloud
 * @param lidarpointclouds 激光地图的文件路径
 * @param 需要跳过的行数，默认为0
 */
	void ReadLidarPointClouds(const std::string lidarpointclouds, const int skipline = 0);

/*
* @brief 读取激光.bin原始数据，并放入成员变量m_cloud
* @param lidarpointclouds 激光.bin的文件路径
*/
	void ReadLidarPointClouds(align_lidar_pair lidarpointclouds);

/*
* @brief 读单侧雷达bin，判断是否在FOV范围后进行坐标转换，数据存于成员变量m_cloud中
* @param label 左激光/右激光
* @param 激光.bin数据存放路径、时间戳、车辆pose
*/
	void readunilaterallidar(std::string label, LidarFileInfo &fileinfo);

/*
* @brief 获得指向激光点云m_cloud的指针
* @return 指向m_cloude的指针
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr GetLidarClouds();

/*
* @brief 清除激光点云m_cloud
*/
	void Clear();
	
private:
/*
* @brief 拆分csv数据
* @param str csv格式数据
* @return 指向m_cloude的指针
*/
	std::vector<std::string> splitstring(const std::string &str);
/*
* @brief 判断自车坐标下的激光数据点是否在LIDARXYFOV，LIDARZFOV范围内
* @param lidarpoint_v 自车坐标下的激光数据
* @return true:在fov范围内 false:不在fov范围内
*/
	bool IsInFov(const PointT lidarpoint_v);
	
private:

	static LidardateCenter instance;
/*
* @brief 全局坐标系下的激光点云
*/
	pcl::PointCloud<pcl::PointXYZI> m_cloud;
/*
* @brief convert实例化
*/
	CLidarDataConvert lidarconvert;
	CPoDataConvert    poconvert;
	

};
