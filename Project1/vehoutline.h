#pragma once
#include "base_struct.h"
#include "cppheader.h"
#include "config.h"
#include "polygon.h"
/*
 * @brief 汉车车辆外轮廓，用于作图
 */
static TPoint vehoutline[37] = 
{
	{ 3.36, 0.95},
	{ 3.456, 0.9 },
	{ 3.598, 0.803},
	{ 3.671, 0.727},
	{ 3.79,	0.508},
	{ 3.842, 0.302},
	{ 3.85,	0.2},
	{ 3.86,	0.15},
	{ 3.87,	0.1},
	{ 3.87, -0.1},
	{ 3.86, -0.15},
	{ 3.85, -0.2},
	{ 3.842, -0.302},
	{ 3.79, -0.508},
	{ 3.671, -0.727},
	{ 3.598, -0.803},
	{ 3.456, -0.9},
	{ 3.36, -0.95},
	{ -0.78, -0.95},
	{ -0.82, -0.9},
	{ -0.886, -0.829},
	{ -0.943, -0.744},
	{ -1, -0.605},
	{ -1.051, -0.428},
	{ -1.073, -0.273},
	{ -1.08, -0.2},
	{ -1.09, -0.15},
	{ -1.09, 0.15},
	{ -1.08, 0.2},
	{ -1.073, 0.273},
	{ -1.051, 0.428},
	{ -1, 0.605},
	{ -0.943, 0.744},
	{ -0.886, 0.829},
	{ -0.82, 0.9},
	{ -0.78, 0.95},
	{ 3.36, 0.95}
};
/*
 * @brief 自车坐标下gt图坐标
 */
static TPoint bevrange[5] =
{
	{(Param_u16VehiDimension_VehiLength - Param_u16VehiDimension_RearBumper2RearAxle) + Const_GtResolutionH* BevPixelResolution,
	Const_GtResolutionH/2 * BevPixelResolution},
	{ (Param_u16VehiDimension_VehiLength - Param_u16VehiDimension_RearBumper2RearAxle) + Const_GtResolutionH * BevPixelResolution,
	-Const_GtResolutionH / 2 * BevPixelResolution},
	{ (Param_u16VehiDimension_VehiLength - Param_u16VehiDimension_RearBumper2RearAxle),
	-Const_GtResolutionH / 2 * BevPixelResolution},
	{(Param_u16VehiDimension_VehiLength - Param_u16VehiDimension_RearBumper2RearAxle),
	Const_GtResolutionH / 2 * BevPixelResolution},
	{(Param_u16VehiDimension_VehiLength - Param_u16VehiDimension_RearBumper2RearAxle) + Const_GtResolutionH * BevPixelResolution,
	Const_GtResolutionH / 2 * BevPixelResolution}
};

//const static CPolygon vehoutline_polygon(vehoutline,36);
//const static CPolygon bevrange_polygon(bevrange,4);

inline TPoint* GetVehoutLine_37()
{
	return vehoutline;
}

inline TPoint* GetBevRange_5()
{
	return bevrange;
}