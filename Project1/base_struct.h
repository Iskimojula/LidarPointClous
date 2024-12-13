#pragma once
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef float               float32;        /* IEEE754-2008 single precision */
typedef double              float64;        /* IEEE754-2008 double precision */
typedef float               float32_t;        /* IEEE754-2008 single precision */
typedef double              float64_t;        /* IEEE754-2008 double precision */
typedef uint64_t TimestampType;

enum  LidarIndex {
	IDLELidar = -1,
	LEFTLidar = 0,
	RIGHTLidar = 1,
	TOPLidar = 2,
	LEFT_BACKLidar = 3,
	RIGHT_BACKLidar = 4
};

typedef struct _PointT {
	float x;
	float y;
	float z;
	uint8_t intensity;
}PointT;

typedef struct _TPose
{
	float32_t x;
	float32_t y;
	float32_t theta;
}TPose;

typedef struct _TPoint
{
	float32_t x;
	float32_t y;

}TPoint, Vec2D;

typedef struct _LidarFileInfo
{
	std::string pos;//left/right
	TimestampType ts;
	TPose po; //dr

	std::string filepath;//ÎÄ¼þÂ·¾¶
}LidarFileInfo;




typedef struct
{
	LidarIndex index;
	double R[3][3];
	double t[3];

}LidarCailData;