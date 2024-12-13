#pragma once
#include "cppheader.h"
#include "poconvert.h"
#include "base_struct.h"
#include <opencv2/opencv.hpp>
/*
 * @brief 多边形类
 */
class CPolygon
{
public:
	CPolygon() {}

/*
* @brief 构造函数，用于创建一个多边形对象
* @param  创建一个x0, y0, x1, y1, x2, y2, x3, y3四边形对象
*/
	CPolygon(float32_t x0, float32_t y0, float32_t x1, float32_t y1,
		float32_t x2, float32_t y2, float32_t x3, float32_t y3)
	{
		TPoint point0 = { x0, y0 };
		TPoint point1 = { x1, y1 };
		TPoint point2 = { x2, y2 };
		TPoint point3 = { x3, y3 };
		m_polygon.push_back(point0);
		m_polygon.push_back(point1);
		m_polygon.push_back(point2);
		m_polygon.push_back(point3);
	}

/*
* @brief 构造函数，用于创建一个多边形对象
* @param  创建一个n边形对象 n = size
*/
	CPolygon(TPoint* point, int size)
	{
		for (int i = 0; i < size; i++)
		{
			m_polygon.push_back(point[i]);
		}
	}

/*
* @brief 将点(x,y)push入多边形
*/
	void push(float32_t x, float32_t y)
	{
		TPoint point = { x, y };
		m_polygon.push_back(point);
	}

/*
* @brief 多边形坐标转换，将整个多边形由自车坐标转为全局坐标
* @param vehpose车辆pose
*/
	void trans2W(const TPose vehpose)
	{
		std::vector<TPoint> m_polygoncopy = m_polygon;
		m_polygon.clear();

		for (auto point : m_polygoncopy)
		{
			m_polygon.push_back(poconvert.trans2W(point, vehpose));
		}
	}

/*
* @brief 判断点（x,y）是否在多边形m_polygon内
*/
	bool Inside(float32_t x, float32_t y)
	{
		const int polygon_size = m_polygon.size();
		if (polygon_size < 3)
		{
			return false;
		}

		bool ret = false;
		TPoint pt = {x,y};
		for (int icnt = 0; icnt < polygon_size; icnt++)
		{
			const TPoint& pt1 = m_polygon[icnt % polygon_size];
			const TPoint& pt2 = m_polygon[(icnt + 1) % polygon_size];

			float min_y = fminf(pt1.y, pt2.y);
			float max_y = fmaxf(pt1.y, pt2.y);
			if (min_y < pt.y && pt.y <= max_y && fminf(pt1.x, pt2.x) <= pt.x)
			{
				if (pt.x > pt2.x + (pt.y - pt2.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y))
				{
					ret = !ret;
				}
			}
		}
		return ret;
	}

/*
* @brief 坐标转换，将std::vector<TPoint>格式转换为pcl::PointCloud<pcl::PointXYZI>格式
* @return 指向静态变量的指针
*/
	pcl::PointCloud<pcl::PointXYZI>::Ptr trans2Cloud()
	{
		static pcl::PointCloud<pcl::PointXYZI> cloud;
		cloud.clear();

		for (int i = 0; i < m_polygon.size(); i++)
		{
			pcl::PointXYZI point;
			point.x = m_polygon[i].x;
			point.y = m_polygon[i].y;
			point.z = 0.0f;
			point.intensity = 255;
			cloud.push_back(point);
		}
		return boost::make_shared < pcl::PointCloud<pcl::PointXYZI>> (cloud);
	}

private:
/*
* @brief 包含多边形顶点的成员变量
*/
	std::vector<TPoint> m_polygon;

/*
* @brief 图像坐标系下的多边形
*/
	std::vector<cv::Point> m_polygon_cv;

/*
* @brief 实例化poconvert
*/
	CPoDataConvert poconvert;
};