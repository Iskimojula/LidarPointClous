#pragma once
#include "lidarcali.h"
#include <Eigen/Dense>
/*
 * @brief ����ת��ģ��Ļ��࣬����convertģ���̳������
 */
class CDataConvert
{
public:
	CDataConvert() {};
	~CDataConvert() {};

public:
	virtual PointT trans2V(const LidarIndex index, const PointT lidardat)
	{
		PointT idel = { 0 };
		return idel;
	}

	virtual TPoint trans2V(const TPoint pointW, const TPose vehpose)
	{
		TPoint idel = { 0 };
		return idel;
	}

	virtual TPoint trans2W(const TPoint pointV, const TPose vehpose)
	{
		TPoint idel = { 0 };
		return idel;
	}
private:

};