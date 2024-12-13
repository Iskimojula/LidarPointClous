#pragma once
#include "dataconvert.h"
/*
 * @brief CDataConvert的派生类，自车坐标系与全局坐标系之间的转换
 */
class CPoDataConvert :public CDataConvert
{
public:
/*
 * @brief 全局坐标系->自车坐标系
 * @param pointW 全局坐标系中的点
 * @param vehpose 车辆pose
 * @return 自车坐标系中的点
 */
	TPoint trans2V(const TPoint pointW, const TPose vehpose)
	{
		Vec2D OV, OW;
		OV.x = vehpose.x;
		OV.y = vehpose.y;

		OW.x = pointW.x;
		OW.y = pointW.y;

		Vec2D VM = Vec_sub(OW, OV);
		float32_t VMmod = Vec_mod(VM);
		float32_t VMtheta = Vec_yaw(VM) - vehpose.theta;

		Vec2D pointV2D = Vec_cart(VMmod, VMtheta);
		TPoint pointV;
		pointV.x = pointV2D.x;
		pointV.y = pointV2D.y;

		return pointV;

	}

/*
 * @brief 自车坐标系->全局坐标系
 * @param pointV 自车坐标系中的点
 * @param vehpose 车辆pose
 * @return 全局坐标系中的点
 */
	TPoint trans2W(const TPoint pointV, const TPose vehpose)
	{
		Vec2D VWL;
		VWL.x = pointV.x;
		VWL.y = pointV.y;
		float32_t theta = Vec_yaw(VWL) + vehpose.theta;
		float32_t VWmod = Vec_mod(VWL);

		Vec2D VW = Vec_cart(VWmod, theta);
		Vec2D OV, OW;
		OV.x = vehpose.x;
		OV.y = vehpose.y;

		OW = Vec_sum(OV, VW);
		TPoint pointW;
		pointW.x = OW.x;
		pointW.y = OW.y;

		return pointW;
	}

/*
* @brief 函数重写，自车坐标系->全局坐标系
* @param point 指向一个TPoint的指针，入参时TPoint为全局坐标系中的点，函数结束时TPoint为自车坐标系中的点
* @param vehpose 车辆pose
*/
	void   trans2V(TPoint *point,const TPose vehpose)
	{
		TPoint pointW = (*point);
		Vec2D OV, OW;
		OV.x = vehpose.x;
		OV.y = vehpose.y;

		OW.x = pointW.x;
		OW.y = pointW.y;

		Vec2D VM = Vec_sub(OW, OV);
		float32_t VMmod = Vec_mod(VM);
		float32_t VMtheta = Vec_yaw(VM) - vehpose.theta;

		Vec2D pointV2D = Vec_cart(VMmod, VMtheta);
	
		(*point).x = pointV2D.x;
		(*point).y = pointV2D.y;
	}
private:
	
/*
* @brief 二维向量减法运算 vec1 - vec2
* @param vec1 被减向量
* @param vec2 减向量
* @return 差向量
*/
	inline Vec2D Vec_sub(const Vec2D vec1, const Vec2D vec2)
	{
		Vec2D subvex;
		subvex.x = vec1.x - vec2.x;
		subvex.y = vec1.y - vec2.y;
		return subvex;
	}

	
/*
* @brief 二维向量求模
* @param vec1 求模向量
* @return 向量的模
*/
	inline float32_t Vec_mod(const Vec2D vec1)
	{
		return  ((float32_t)sqrt(pow(vec1.x, 2) + pow(vec1.y, 2)));
	}

	
/*
* @brief 二维向量求与极轴的倾角
* @param vec1 输入向量
* @return 向量的倾角
*/
	inline float32_t Vec_yaw(const Vec2D vec1)
	{
		return  atan2f(vec1.y, vec1.x);//-pi - pi
	}

	
/*
* @brief 二维向量由极坐标转为平面坐标
* @param mod 向量的模
* @param theta 向量的倾角
* @return 向量的平面坐标
*/
	inline Vec2D Vec_cart(const float32_t mod, const float32_t theta)
	{
		Vec2D vex;
		vex.x = mod * ((float32_t)cos(theta));
		vex.y = mod * ((float32_t)sin(theta));
		return vex;
	}
	
/*
* @brief 二维向量由和 vec1 + vec2
* @param vec1 ，vec2 两个用于求和的向量
* @return 向量的和
*/
	inline Vec2D Vec_sum(const Vec2D vec1, const Vec2D vec2)
	{
		Vec2D sumvex;
		sumvex.x = vec1.x + vec2.x;
		sumvex.y = vec1.y + vec2.y;
		return sumvex;
	}
};
