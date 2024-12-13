#pragma once
/*
 * @brief 配置文件
 */
#include "cppheader.h"
constexpr auto DIRPATH = "E:/data/uss/lidar/imu_us_test_0715/record_2024-7-15-14-46-33/bilateralLidar/merge_1721025993777439_1721025993785849_8410.csv";
//constexpr auto LIDARFOLDER = "E:/data/lidar/log/2024.8.30/record_2024-8-30-15-56-51";
constexpr auto LEFTLIDARFOLDER = "LIDAR_LEFT"; //左激光bin文件夹
constexpr auto RIGHTLIDARFOLDER = "LIDAR_RIGHT"; //右激光bin文件夹
constexpr auto USSFOLDER = "USS";
constexpr auto OUTMAPFILE = "map.csv";
constexpr auto USSFILE = "USS.csv";
constexpr auto GTFOLDER = "GT";
constexpr auto LIDARXYFOV = 20.0f;//自车坐标下激光点xy范围
constexpr auto LIDARZFOV  = 1.0f;//激光点自车坐标z轴范围

constexpr auto PODOWNSAMPLE = 0.5f; //lidar po每隔50cm取一帧
constexpr auto USSDOWNSAMPLE = 0.0f; //车辆每行驶5cm取一张超声数据图 ,当数值为0时，只要行驶便会记录

constexpr auto VOXELESFSIZE = 0.05f; //体素值
constexpr auto PIXELSIZE = 0.05;     //图像冗余边界

constexpr auto EULERDIS = 0.2f;      //欧拉聚类距离
constexpr auto MINCLUSTERDIS = 6;	 //最少的聚类点

constexpr auto RANGEX_MIN = 2.911f;  //旧版调试数据，未使用
constexpr auto RANGEX_MAX = 18.0f;   //旧版调试数据，未使用

constexpr auto RANGEY_MIN = -9.5f;   //旧版调试数据，未使用
constexpr auto RANGEY_MAX = 9.5f;    //旧版调试数据，未使用

constexpr auto RANGEZ_MIN = 0.0f;    //如果不时标注路沿石，那么小于RANGEZ_MIN的点云不会被用去建图
constexpr auto RANGEZ_MAX = 1.0f;	 //与LIDARZFOV值相同

/*bev和车辆参数*/
constexpr auto BevGridEdgeX_Rear_m  = -6.080f;
constexpr auto BevGridEdgeX_Front_m = 8.900f;
constexpr auto BevGridEdgeY_Right_m = -6.000f;
constexpr auto BevGridEdgeY_Left_m  = 5.980f;

constexpr auto Param_u16VehiDimension_VehiLength = 4.700f;
constexpr auto Param_u16VehiDimension_VehiWidth = 1.910f;
constexpr auto Param_u16VehiDimension_RearBumper2RearAxle = 0.940f;

constexpr auto Const_BevResolutionH = 600;
constexpr auto Const_BevResolutionV = 750;

constexpr auto Const_GtResolutionH = 128;
constexpr auto Const_GtResolutionV = 128;

constexpr auto VehiCoordO_RowIdx = 445;
constexpr auto VehiCoordO_ColIdx = 299;

constexpr auto BevPixelResolution = 0.02f;//bev 像素分辨率2cm
