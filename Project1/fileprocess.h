#pragma once
#include "cppheader.h"
#include "config.h"
#include "base_struct.h"
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

typedef std::pair<LidarFileInfo, LidarFileInfo> align_lidar_pair;

/*
 * @brief ԭʼ��������bin�ļ���ts,dr��Ϣ����ģ��
 */
class FileProcess
{
public:
	FileProcess() {};
	~FileProcess() {};

/*
* @brief �������������Գ������µļ������boundary����gtͼ��.png��
* @param
*/
	void Process();

/*
* @brief ���һ��ָ��m_lidarfilelist��Ա������ָ��
*/
	boost::shared_ptr<std::vector<align_lidar_pair>> GetLidarAlignFileList();

/*
* @brief ���һ��ָ��m_po��Ա������ָ��
*/
	boost::shared_ptr<std::map<TimestampType, TPose>> GetPoMap();
private:

/*
* @brief ��ȡһ��ԭʼ����bin�����ļ�������ȡ����ts,dr,�ļ�·����Ϣ
* @param folderpath ԭʼ����.bin���������ļ��е�·����LIDAR_LEFT,LIDAR_RIGHT��
* @param label ����λ�ã��󼤹�/�Ҽ���
* @param lidarinfo ����ļ�������ts,dr,�ļ�·����Ϣ�б�
*/
	void readlidarfolder(const std::string folderpath,const std::string label,std::vector<LidarFileInfo> &lidarinfo);

/*
* @brief ȥ���ļ���׺��ֻ��ȡһ���ļ����ļ���
* @param filename ������׺���ļ���
* @return ������׺���ļ���
*/
	std::string removeFileExtension(const std::string& filename);

/*
* @brief ���ݼ����ļ�����ȡһ������.bin�ļ���ts,po��Ϣ
* @param filename ����.bin�ļ�·��
* @param ts ����ʱ���
* @param po ����dr
* @return ����ʱ���
*/
	TimestampType getlidarinfo(const std::string filename, TimestampType &ts, TPose &po);

/*
* @brief ���Ҽ�������ʱ�����
* @param left һ���󼤹�ts,dr����
* @param rightlist �Ҽ���ts,dr�б�
* @return ʱ��������󼤹⣬�Ҽ����
*/
	align_lidar_pair lidarTsAlignment(const LidarFileInfo left,const std::vector<LidarFileInfo> & rightlist);
	void lidarfiledownsampling();
private:

/*
* @brief ��Ա������ʱ�����ļ���.bin�����ļ����б�
*/
	std::vector<align_lidar_pair> m_lidarfilelist;

/*
* @brief ��Ա���������ݼ���.bin�ļ��������� ����ts_dr�б�
*/
	std::map<TimestampType, TPose> m_po;
	

};

