#pragma once
#include "cppheader.h"
#include "argumentpass.h"
#include <boost/filesystem.hpp>

#if 1
inline uint8_t getrandcolor()
{
	float color = static_cast<float>(rand()) / static_cast<float> (RAND_MAX);
	return static_cast<uint8_t> (color * 255);
}

inline void printProgressBar(int progress, int total) {
	float percentage = static_cast<float>(progress) / total;
	int barWidth = 50;

	std::cout << "[";
	int pos = barWidth * percentage;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(percentage * 100.0) << " %\r";
	if (progress == total)
	{
		std::cout << "\n" << std::endl;
	}
	std::cout.flush();
	
}
//��С�����Ų�
inline bool compare_y(const cv::Point2f &p1, const cv::Point2f &p2) 
{ 
	return (p1.y < p2.y); 
}

inline bool compare_x(const cv::Point &p1 , const cv::Point &p2)
{
	return (p1.x < p2.x);
}
//��ʼ������鼤�⡢�����ļ����Ƿ����
inline bool checkLidarFoldervaild(std::string folderpath)
{
	boost::filesystem::path parent_directory(folderpath);
	if (boost::filesystem::exists(parent_directory))
	{
		std::cout << "Data folder path: " << folderpath << std::endl;
		std::string leftlidar = folderpath + "/" + std::string(LEFTLIDARFOLDER);
		boost::filesystem::path leftlidar_directory(folderpath);

		std::string rightlidar = folderpath + "/" + std::string(RIGHTLIDARFOLDER);
		boost::filesystem::path rightlidar_directory(folderpath);

		std::string uss = folderpath + "/" + std::string(USSFOLDER);
		boost::filesystem::path uss_directory(folderpath);

		if (boost::filesystem::exists(leftlidar_directory) && boost::filesystem::exists(rightlidar_directory) &&
			boost::filesystem::exists(uss_directory))
		{
			std::cout << "Data folder lidar , uss exists !" << std::endl;
			return true;
		}
		else
		{
			std::cerr << "error: Data folder not complete, please check! !" << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "error: Data folder not exist, please check! !" << std::endl;
		return false;
	}
}

//�ļ��г�ʼ�����������������ļ��У��½�һ���ļ��У������������ļ��У���ôɾ���ļ����µ������ļ�
inline void outfoldercheck(std::string gtfolderpath)
{
	if (!boost::filesystem::exists(gtfolderpath))
	{
		std::cout << "gt folder does not exist! makdir new folder GT !" << std::endl;
		boost::filesystem::create_directory(gtfolderpath);
		boost::filesystem::create_directory(ArgumentPass::Instance().get_gtfolderpath());
	}
	else
	{
		boost::filesystem::path pathToRemove(gtfolderpath);

		if (boost::filesystem::exists(pathToRemove) && boost::filesystem::is_directory(pathToRemove))
		{
			for (boost::filesystem::directory_iterator it(pathToRemove); it != boost::filesystem::directory_iterator(); ++it)
			{
				boost::filesystem::remove_all(it->path());
			}
		}
		boost::filesystem::create_directory(ArgumentPass::Instance().get_gtfolderpath());
		std::cout << "gt folder exists ! remove all files in gt folder !" << std::endl;
	}
}
//ɾ��ĳ���ļ���
inline void removefolder(std::string folder)
{
	if (boost::filesystem::exists(folder) && boost::filesystem::is_directory(folder)) {
		try {
			boost::filesystem::remove_all(folder); // ɾ���ļ��м�����������
			std::cout << "Folder deleted successfully." << std::endl;
		}
		catch (const boost::filesystem::filesystem_error& ex) {
			std::cerr << "Error deleting folder: " << ex.what() << std::endl;
		}
	}
	else {
		std::cout << "Folder not found." << std::endl;
	}

}
//�½��ļ��У��������ļ����Ѿ����ڣ���ôɾ������ļ���
inline void newfolder(std::string folder)
{
	if (!boost::filesystem::exists(folder))
	{
		boost::filesystem::create_directory(folder);
	}
	else
	{
		removefolder(folder);
		boost::filesystem::create_directory(folder);
	}
}

inline int find1stdigitinstring(std:: string str)
{
	int index = 0;
	for (char c : str)
	{
		if (std::isdigit(c))
		{
			return index;
		}
		index++;
	}
	return index;
}
inline std::string getprefix(std::string folderpath)
{
	std::string name;
	boost::filesystem::path folderPath(folderpath); // �滻Ϊ��Ҫ�������ļ���·��

	if (boost::filesystem::exists(folderPath) && boost::filesystem::is_directory(folderPath)) {
		for (const auto& entry : boost::filesystem::directory_iterator(folderPath)) {
			if (boost::filesystem::is_regular_file(entry.path()) && (entry.path().extension().string() == ".mkv")) {
				std::string fileName = entry.path().stem().string(); // ��ȡ������׺���ļ���

				return fileName.substr(find1stdigitinstring(fileName));
			}
		}
	}
	else {
		std::cout << "Folder does not exist or is not a directory." << std::endl;
	}
	return name;
}
#endif