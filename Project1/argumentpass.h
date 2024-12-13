#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include "config.h"
/*
 * @brief ����ģʽ���洢�ն������������
 *
 */
class ArgumentPass
{
public:
	ArgumentPass() {};
	~ArgumentPass() {};
	static ArgumentPass& Instance() ;
public:
	//�����ļ�·��
	std::string LIDARFOLDE_arg;
	
	//������
	std::string GTPREFIX_arg;
	
	//�Ƿ���·��ʯ
	bool IsRoadTrafficStone;
	
	//���gt�ļ��еĹ���·��
	std::string get_gtfolderworkdir()
	{
		return (std::string(LIDARFOLDE_arg) + "/" + std::string(GTPREFIX_arg));
	}
	//���gtͼ�����ļ���·��
	std::string get_gtfolderpath()
	{
		return (get_gtfolderworkdir() + "/uss_bev_train_data");
	}

	std::string get_outcsvpath()
	{
		return get_gtfolderworkdir();
	}
	//���gt����csv·��
	std::string get_outcsvbasename()
	{
		return (get_gtfolderworkdir() + "/" + GTPREFIX_arg + ".csv");
	}

	std::string get_lidarmap()
	{
		return (LIDARFOLDE_arg + "/" + std::string(GTFOLDER));
	}

private:
	static ArgumentPass instance;
	

};

