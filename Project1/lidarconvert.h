#pragma once
#include "dataconvert.h"
/*
 * @brief CDataConvert的派生类，激光坐标系->自车坐标系
 * x_vehicl = R*x_lidar + t
 * R为旋转矩阵，t为平移向量
 * 参考文本： https://blog.csdn.net/m0_68312479/article/details/128266483
 */
class CLidarDataConvert :public CDataConvert
{

public:
	PointT trans2V(const LidarIndex index, const PointT lidardat)
	{
		LidarCailData calidat = GetLidarCaliDat(index);
		Eigen::Matrix3d R;
		R << calidat.R[0][0], calidat.R[0][1], calidat.R[0][2],
			calidat.R[1][0], calidat.R[1][1], calidat.R[1][2],
			calidat.R[2][0], calidat.R[2][1], calidat.R[2][2];

		Eigen::Matrix<double, 3, 1> t;
		t << calidat.t[0], calidat.t[1], calidat.t[2];

		Eigen::Matrix<double, 3, 1> X_Lidar;
		X_Lidar << lidardat.x, lidardat.y, lidardat.z;

		Eigen::Matrix<double, 3, 1> X_Vehicle = R * X_Lidar + t;

		PointT vehicledat = { (float32_t)X_Vehicle(0),(float32_t)X_Vehicle(1),(float32_t)X_Vehicle(2),lidardat.intensity };
		return  vehicledat;
	}


private:

};