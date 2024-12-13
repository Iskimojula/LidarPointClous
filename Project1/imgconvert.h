#pragma once
#include "dataconvert.h"
#include <opencv2/opencv.hpp>
#include "config.h"
/*
 * @brief CDataConvert�������࣬�Գ�����ϵ->ͼ������ϵ
 */
class CImgDataConvert : public CDataConvert
{
public:
	cv::Point Trans2Img(float32_t x0, float32_t y0)
	{
		 cv::Point pt(VehiCoordO_ColIdx- std::ceil(y0/ BevPixelResolution)-235, VehiCoordO_RowIdx - std::ceil(x0 / BevPixelResolution)-129);
		 return pt;
	}

private:

};


