#pragma once
#include "dataconvert.h"
/*
 * @brief CDataConvert�������࣬�Գ�����ϵ��ȫ������ϵ֮���ת��
 */
class CPoDataConvert :public CDataConvert
{
public:
/*
 * @brief ȫ������ϵ->�Գ�����ϵ
 * @param pointW ȫ������ϵ�еĵ�
 * @param vehpose ����pose
 * @return �Գ�����ϵ�еĵ�
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
 * @brief �Գ�����ϵ->ȫ������ϵ
 * @param pointV �Գ�����ϵ�еĵ�
 * @param vehpose ����pose
 * @return ȫ������ϵ�еĵ�
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
* @brief ������д���Գ�����ϵ->ȫ������ϵ
* @param point ָ��һ��TPoint��ָ�룬���ʱTPointΪȫ������ϵ�еĵ㣬��������ʱTPointΪ�Գ�����ϵ�еĵ�
* @param vehpose ����pose
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
* @brief ��ά������������ vec1 - vec2
* @param vec1 ��������
* @param vec2 ������
* @return ������
*/
	inline Vec2D Vec_sub(const Vec2D vec1, const Vec2D vec2)
	{
		Vec2D subvex;
		subvex.x = vec1.x - vec2.x;
		subvex.y = vec1.y - vec2.y;
		return subvex;
	}

	
/*
* @brief ��ά������ģ
* @param vec1 ��ģ����
* @return ������ģ
*/
	inline float32_t Vec_mod(const Vec2D vec1)
	{
		return  ((float32_t)sqrt(pow(vec1.x, 2) + pow(vec1.y, 2)));
	}

	
/*
* @brief ��ά�������뼫������
* @param vec1 ��������
* @return ���������
*/
	inline float32_t Vec_yaw(const Vec2D vec1)
	{
		return  atan2f(vec1.y, vec1.x);//-pi - pi
	}

	
/*
* @brief ��ά�����ɼ�����תΪƽ������
* @param mod ������ģ
* @param theta ���������
* @return ������ƽ������
*/
	inline Vec2D Vec_cart(const float32_t mod, const float32_t theta)
	{
		Vec2D vex;
		vex.x = mod * ((float32_t)cos(theta));
		vex.y = mod * ((float32_t)sin(theta));
		return vex;
	}
	
/*
* @brief ��ά�����ɺ� vec1 + vec2
* @param vec1 ��vec2 ����������͵�����
* @return �����ĺ�
*/
	inline Vec2D Vec_sum(const Vec2D vec1, const Vec2D vec2)
	{
		Vec2D sumvex;
		sumvex.x = vec1.x + vec2.x;
		sumvex.y = vec1.y + vec2.y;
		return sumvex;
	}
};
