#pragma once
#include "cppheader.h"
#include "config.h"
#include "base_struct.h"
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

typedef std::pair<LidarFileInfo, LidarFileInfo> align_lidar_pair;

/*
 * @brief 原始激光数据bin文件名ts,dr信息处理模块
 */
class FileProcess
{
public:
	FileProcess() {};
	~FileProcess() {};

/*
* @brief 主函数，根据自车坐标下的激光点云boundary生成gt图（.png）
* @param
*/
	void Process();

/*
* @brief 获得一个指向m_lidarfilelist成员变量的指针
*/
	boost::shared_ptr<std::vector<align_lidar_pair>> GetLidarAlignFileList();

/*
* @brief 获得一个指向m_po成员变量的指针
*/
	boost::shared_ptr<std::map<TimestampType, TPose>> GetPoMap();
private:

/*
* @brief 读取一侧原始激光bin数据文件名，获取激光ts,dr,文件路径信息
* @param folderpath 原始激光.bin数据所在文件夹的路径（LIDAR_LEFT,LIDAR_RIGHT）
* @param label 激光位置，左激光/右激光
* @param lidarinfo 输出的激光数据ts,dr,文件路径信息列表
*/
	void readlidarfolder(const std::string folderpath,const std::string label,std::vector<LidarFileInfo> &lidarinfo);

/*
* @brief 去掉文件后缀，只读取一个文件的文件名
* @param filename 包含后缀的文件名
* @return 不含后缀的文件名
*/
	std::string removeFileExtension(const std::string& filename);

/*
* @brief 根据激光文件名获取一个激光.bin文件的ts,po信息
* @param filename 激光.bin文件路径
* @param ts 激光时间戳
* @param po 车辆dr
* @return 激光时间戳
*/
	TimestampType getlidarinfo(const std::string filename, TimestampType &ts, TPose &po);

/*
* @brief 左右激光数据时间对齐
* @param left 一个左激光ts,dr数据
* @param rightlist 右激光ts,dr列表
* @return 时间对齐后的左激光，右激光对
*/
	align_lidar_pair lidarTsAlignment(const LidarFileInfo left,const std::vector<LidarFileInfo> & rightlist);
	void lidarfiledownsampling();
private:

/*
* @brief 成员变量，时间对齐的激光.bin数据文件名列表
*/
	std::vector<align_lidar_pair> m_lidarfilelist;

/*
* @brief 成员变量，根据激光.bin文件名建立的 激光ts_dr列表
*/
	std::map<TimestampType, TPose> m_po;
	

};

