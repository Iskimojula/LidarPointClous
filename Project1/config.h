#pragma once
/*
 * @brief �����ļ�
 */
#include "cppheader.h"
constexpr auto DIRPATH = "E:/data/uss/lidar/imu_us_test_0715/record_2024-7-15-14-46-33/bilateralLidar/merge_1721025993777439_1721025993785849_8410.csv";
//constexpr auto LIDARFOLDER = "E:/data/lidar/log/2024.8.30/record_2024-8-30-15-56-51";
constexpr auto LEFTLIDARFOLDER = "LIDAR_LEFT"; //�󼤹�bin�ļ���
constexpr auto RIGHTLIDARFOLDER = "LIDAR_RIGHT"; //�Ҽ���bin�ļ���
constexpr auto USSFOLDER = "USS";
constexpr auto OUTMAPFILE = "map.csv";
constexpr auto USSFILE = "USS.csv";
constexpr auto GTFOLDER = "GT";
constexpr auto LIDARXYFOV = 20.0f;//�Գ������¼����xy��Χ
constexpr auto LIDARZFOV  = 1.0f;//������Գ�����z�᷶Χ

constexpr auto PODOWNSAMPLE = 0.5f; //lidar poÿ��50cmȡһ֡
constexpr auto USSDOWNSAMPLE = 0.0f; //����ÿ��ʻ5cmȡһ�ų�������ͼ ,����ֵΪ0ʱ��ֻҪ��ʻ����¼

constexpr auto VOXELESFSIZE = 0.05f; //����ֵ
constexpr auto PIXELSIZE = 0.05;     //ͼ������߽�

constexpr auto EULERDIS = 0.2f;      //ŷ���������
constexpr auto MINCLUSTERDIS = 6;	 //���ٵľ����

constexpr auto RANGEX_MIN = 2.911f;  //�ɰ�������ݣ�δʹ��
constexpr auto RANGEX_MAX = 18.0f;   //�ɰ�������ݣ�δʹ��

constexpr auto RANGEY_MIN = -9.5f;   //�ɰ�������ݣ�δʹ��
constexpr auto RANGEY_MAX = 9.5f;    //�ɰ�������ݣ�δʹ��

constexpr auto RANGEZ_MIN = 0.0f;    //�����ʱ��ע·��ʯ����ôС��RANGEZ_MIN�ĵ��Ʋ��ᱻ��ȥ��ͼ
constexpr auto RANGEZ_MAX = 1.0f;	 //��LIDARZFOVֵ��ͬ

/*bev�ͳ�������*/
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

constexpr auto BevPixelResolution = 0.02f;//bev ���طֱ���2cm
