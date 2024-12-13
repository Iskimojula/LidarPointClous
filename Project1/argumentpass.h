#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include "config.h"
/*
 * @brief 单例模式，存储终端输入参数的类
 *
 */
class ArgumentPass
{
public:
	ArgumentPass() {};
	~ArgumentPass() {};
	static ArgumentPass& Instance() ;
public:
	//工作文件路径
	std::string LIDARFOLDE_arg;
	
	//工程名
	std::string GTPREFIX_arg;
	
	//是否是路沿石
	bool IsRoadTrafficStone;
	
	//获得gt文件夹的工作路径
	std::string get_gtfolderworkdir()
	{
		return (std::string(LIDARFOLDE_arg) + "/" + std::string(GTPREFIX_arg));
	}
	//获得gt图所在文件的路径
	std::string get_gtfolderpath()
	{
		return (get_gtfolderworkdir() + "/uss_bev_train_data");
	}

	std::string get_outcsvpath()
	{
		return get_gtfolderworkdir();
	}
	//获得gt超声csv路径
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

