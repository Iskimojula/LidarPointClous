#pragma once
#include "lidarcali.h"
#include <Eigen/Dense>
/*
 * @brief 坐标转换模块的基类，其它convert模块会继承这个类
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