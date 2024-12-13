#pragma once
#include "stdint.h"
#include <stdbool.h>
typedef float              float32_t;
typedef float32_t tUSH_Temperature_degC;		///< air temperature
typedef float32_t   matrixf32;
typedef uint32_t    matrixu32;
typedef uint8_t     matrixu8;
typedef uint8_t     Tflag;
typedef float32_t   ratiof32;                                               //================= Ultrasoic App file =======================
typedef unsigned char       boolean;        /* for use with TRUE/FALSE      */
typedef int8_t sint8;
typedef int16_t sint16;
typedef int32_t sint32;
typedef int64_t sint64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef float               float32;        /* IEEE754-2008 single precision */
typedef double              float64;        /* IEEE754-2008 double precision */
typedef int32_t tVehi_VehiType;
typedef uint64_t TimestampType;
typedef uint8   Imgpixel;

typedef  double float64;

#define OD_NUM_MAX 50U  /* max number of object detection index */
#define FS_BOUND_NUM_MAX 160U  /* max number of free space boundary index */
#define PDC_ZONE_NUM 20U  /* number of PDC warnning zone, side(1*4)+R/F(8*2) */
#define PEB_ZONE_NUM 92U  /* number of PEB warnning zone, side(5*4)+R/F(36*2) */
#define MEB_ZONE_NUM 100U  /* number of MEB warnning zone, side(5*4)+R/F(40*2) */
#define SOC_US_OD_NUM_MAX 50U  /* max number of object detection index */
#define SOC_US_FS_BOUND_NUM_MAX 512U  /* max number of free space boundary index */
#define SOC_US_PDC_ZONE_NUM 20U  /* number of PDC warnning zone */
#define SOC_US_PLD_NUM_MAX_UPLD 10U  /* max number of ultrasonic PLD index */
#define USH_ECHO_NUM_MAX 5U  /* 5 echoes */
#define USH_ONE_SND_MULT_RCV_MAX 3U  /* one send multiple receive max */
typedef enum _ttSupportSts
{
	NOT_SUPPORT,
	SUPPORT

}tSupportSts;


typedef enum _ttVehiGear
{
	VEHI_GEAR_P,
	VEHI_GEAR_R,
	VEHI_GEAR_N,
	VEHI_GEAR_D,
	VEHI_GEAR_INVALID

}tVehiGear;

typedef enum _ttActiveSts
{
	NOT_ACTIVED,
	ACTIVED

}tActiveSts;
typedef enum _ttAPA_UltrasonicSts
{
	APA_US_STS_OFF = 0,  // 功能关闭
	APA_US_STS_INIT = 1,  // Initializing
	APA_US_STS_STANDBY = 2,  // standby
	APA_US_STS_SUCCESS = 3,  // 成功
	APA_US_STS_LIMITED = 4,  // Limited Functions
	APA_US_STS_FAILED = 5  // 失败

}tAPA_UltrasonicSts;

typedef enum _ttAPA_FunctionSts
{
	APA_FUNC_OFF = 0,  // 功能关闭
	APA_FUNC_STANDBY = 1,  // standby
	APA_FUNC_SUCCESS = 2,  // 成功
	APA_FUNC_FAILED = 3  // 失败

}tAPA_FunctionSts;

typedef enum _ttAPA_ObjType
{
	OBJ_TYPE_INVALID = 0,
	OBJ_TYPE_DEFAULT = 1,
	OBJ_TYPE_BERTH_PERPENDICULAR,
	OBJ_TYPE_BERTH_PARALLEL,
	OBJ_TYPE_BERTH_SLANTED_30_DEG,
	OBJ_TYPE_BERTH_SLANTED_45_DEG,
	OBJ_TYPE_BERTH_SLANTED_60_DEG,
	OBJ_TYPE_BERTH_MECHANISM,
	OBJ_TYPE_OBSTACALE_US,
	OBJ_TYPE_OBSTACALE_VIS,
	OBJ_TYPE_OBSTACALE_US_LOW,
	OBJ_TYPE_OBSTACALE_US_HIGH

}tAPA_ObjType;

typedef enum _tPixelLabel
{
	eLABEL_UNKNOW = 0,  // class_unknow
	eLABEL_VEHICLE = 1,  // class_vehicle
	eLABEL_ROAD = 2,  // class_road
	eLABEL_PERSON = 3,  // class_pedestrian
	eLABEL_ZEBRA = 4,  // class_zebra_crossing, not now, for placeholder
	eLABEL_PARKINGLINE = 5,  // class_parkingline, not now, for placeholder
	eLABEL_ROADARROW = 6,  // class_road_arrow, not now, for placeholder
	eLABEL_CURBSTONE = 7,  // class_curb
	eLABEL_WALLCOLUMN = 8,  // class_wallcolumn
	eLABEL_SPEEDBUMP = 9,  // class_Speed_bump
	eLABEL_LANELINE = 10,  // class_lane_line, not now, for placeholder
	eLABEL_PARKLOCK = 11,  // class_parking_lock
	eLABEL_VEHSTOPER = 12,  // class_veh_stoper
	eLABEL_TRAFFCONE = 13,  // class_traffic_cone
	eLABEL_OBSTACLE = 14,  // class_obstace
	eLABEL_PARKAREA = 15,  // class_dd, not now, for placeholder
	eLABEL_TOTALNUM//classnum  // classnum,

}PixelLabel;
typedef enum _ttUSH_UsIdx
{
	US_IDX_APA_FRS = 0,  // Comments.
	US_IDX_APA_RRS = 1,  // Comments.
	US_IDX_APA_FLS = 2,  // Comments.
	US_IDX_APA_RLS = 3,  // Comments.
	US_IDX_PDC_RRC = 4,  // Comments.
	US_IDX_PDC_RRM = 5,  // Comments.
	US_IDX_PDC_RLM = 6,  // Comments.
	US_IDX_PDC_RLC = 7,  // Comments.
	US_IDX_PDC_FLC = 8,  // Comments.
	US_IDX_PDC_FLM = 9,  // Comments.
	US_IDX_PDC_FRM = 10,  // Comments.
	US_IDX_PDC_FRC = 11,  // Comments.
	US_IDX_NUM_MAX = 12,  // Comments.
	US_IDX_APA_PDC_BOUND = US_IDX_PDC_RRC,  // APA & UPA boundary.
	US_IDX_ALL_IDX = 0xFE,  // Including 0~11 sensors.
	US_IDX_INVALID = 0xFF  // Comments.

}tUSH_UsIdx;

typedef enum _ttPDC_AudioWarnLv
{
	PDC_AUD_WARN_LV_NONE = 0,  // 无声音告警
	PDC_AUD_WARN_LV_LONG_BEEP = 1,  // 告警长鸣
	PDC_AUD_WARN_LV_2 = 2,  // 二档声音告警
	PDC_AUD_WARN_LV_3 = 3,  // 三档声音告警
	PDC_AUD_WARN_LV_4 = 4,  // 四档声音告警
	PDC_AUD_WARN_LV_5 = 5,  // 五档声音告警
	PDC_AUD_WARN_LV_6 = 6,  // 六档声音告警
	PDC_AUD_WARN_LV_7 = 7,  // 七档声音告警
	PDC_AUD_WARN_LV_8 = 8,  // 八档声音告警
	PDC_AUD_WARN_LV_9 = 9,  // 九档声音告警
	PDC_AUD_WARN_LV_10 = 10  // 十档声音告警

}tPDC_AudioWarnLv;

typedef enum _ttAPA_UlrasonicPldSts
{
	APA_UPLD_OFF = 0,  // off / 故障
	APA_UPLD_STANDBY = 1,  // standby
	APA_UPLD_NO_BERTH = 2,  // 无可泊车位
	APA_UPLD_BERTH = 3  // 有可泊车位

}tAPA_UlrasonicPldSts;

typedef enum _ttAPA_PldBerthAvailable
{
	PLD_BERTH_NONE = 0,  // 无库位
	PLD_BERTH_NOT_AVAILABLE,  // 有库位，库位不可用
	PLD_BERTH_AVAILABLE,  // 有库位，库位可用
	PLD_BERTH_SELECTED  // 有库位，已选择该库位

}tAPA_PldBerthAvailable;
typedef enum _ttWheelDirection
{
	WHEEL_DIR_STANDSTILL = 0,
	WHEEL_DIR_FORWARD,
	WHEEL_DIR_BACKWARD,
	WHEEL_DIR_INVALID

}tWheelDirection;
typedef enum _ttUSH_MeasurementProfile
{
	USH_MEASUREMENT_PROFILE_A,  // Comments.
	USH_MEASUREMENT_PROFILE_B,  // Comments.
	USH_MEASUREMENT_PROFILE_C,  // Comments.
	USH_MEASUREMENT_PROFILE_ENVELOPE,  // Comments.
	USH_MEASUREMENT_PROFILE_NONE,
	USH_MEASUREMENT_PROFILE_NUM  // Comments.

}tUSH_MeasurementProfile;
typedef enum _ttUSH_UsExtendSts
{
	USH_EXTEND_STS_NONE = 0x0000,  // Comments.
	USH_EXTEND_STS_BLIND_DETECT = 0x0001,  // blind zone detect.
	USH_EXTEND_STS_DIRECT_WAVE = 0x0002,  // direct wave shield.
	USH_EXTEND_STS_MULTI_ECHO = 0x0004,  // multi-reflection echo cancellation.
	USH_EXTEND_STS_CHAN_INTERFERE = 0x0008,  // co-channel interference.
	USH_EXTEND_STS_NOISE = 0x0010,  // @see USH_DIAG_NOISE.
	USH_EXTEND_STS_EXTEND_RECEIVE = 0x0020,  // receive sensor receive impossible echo
	USH_EXTEND_STS_RINGINGTIME_BOOST = 0x0040,  // ringing time boost echo
	USH_EXTEND_STS_HIGH_OBJ = 0x0080,
	USH_EXTEND_STS_STRONG_ECHO_SIGNAL = 0x0100,
	USH_EXTEND_STS_UNSCHEDULED_RECEIVE = 0x0200,  // receive echo in silent receive cycle
	USH_EXTEND_STS_ALL_MASK = 0x07FF

}tUSH_UsExtendSts;

typedef enum _ttUSH_UsSensorDiag
{
	USH_DIAG_NORMAL = 0x00000000U,  // US sensor normal.
	USH_DIAG_NOISE = 0x00000001U,  // Noise detected during last measurement command.
	USH_DIAG_FREQ_DEV_RING = 0x00000004U,  // ringing frequency deviation, |freq_dev|.
	USH_DIAG_FREQ_DEV_TRANS_RESP = 0x00000008U,  // frequency deviation between the transducer driver and its resonance frequency.
	USH_DIAG_TEMPORARY_FAILURE_MASK = 0x0000000DU,  // ***********************************************************
	USH_DIAG_DRIVER_IO_CHECK_ERR = 0x00000010U,
	USH_DIAG_SENSOR_IO_CHECK_ERR = 0x00000020U,
	USH_DIAG_READBACK_CHECK_ERR = 0x00000040U,
	USH_DIAG_VOLT_ERR = 0x00000080U,  // Indication that a supply voltage outside spec occurred or
	USH_DIAG_THRES_N_ACTIVE = 0x00000100U,  // Transmitted threshold values NOT active.
	USH_DIAG_MEAS_N_ACTIVE = 0x00000200U,  // Transmitted measurement profiles NOT active.
	USH_DIAG_OUTER_PARM_ERR_MASK = 0x00000380U,
	USH_DIAG_OV = 0x00000400U,  // Overvoltage detected during last measurement cycle.
	USH_DIAG_UV = 0x00000800U,  // Undervoltage detected during last measurement cycle.
	USH_DIAG_VAL_ERR_MASK = 0x00000C00U,
	USH_DIAG_SC = 0x00001000U,  // US sensor IO short circuit.
	USH_DIAG_OC = 0x00002000U,  // US sensor IO open circuit.
	USH_DIAG_OT = 0x00004000U,  // US sensor temperature > 80degC.
	USH_DIAG_G_DIG_DEV = 0x00008000U,  // Digital amplifier gain deviation.
	USH_DIAG_G_ANA_DEV = 0x00010000U,  // Analog amplifier gain deviation.
	USH_DIAG_I_DRV_DEV = 0x00020000U,  // Transducer driver output current deviation.
	USH_DIAG_F_DRV_DEV = 0x00040000U,  // Driver frequency deviation.
	USH_DIAG_CHIP_ID_INV = 0x00080000U,  // Chip ID read result equals 0
	USH_DIAG_EOL_FAILURE = 0x00100000U,
	USH_DIAG_EE_CHECK_ERR = 0x00200000U,
	USH_DIAG_FREQ_DEV = 0x00400000U,
	USH_DIAG_PWR_FAILURE = 0x00800000U,
	USH_DIAG_DRIVER_FAILURE = 0x01000000U,
	USH_DIAG_ALGO_SIG_ABNORMAL = 0x02000000U,
	USH_DIAG_RINGING_TIME_DEV = 0x04000000U,
	USH_DIAG_INNER_PARM_ERR_MASK = 0x003F8000U,
	USH_DIAG_SCOC = 0x00003000U,
	USH_DIAG_ECHO_DEV = 0x04400000U,
	USH_DIAG_CLOSE_DETECT_MASK = 0x003FFF80U,
	USH_DIAG_DRIVER_COMM_ERR_MASK = 0x00400070U,
	USH_DIAG_SERIOUS_FAILURE_MASK = 0x07FFFFF0U,  // ***********************************************************
	USH_DIAG_ALL_FAILURES_MASK = (USH_DIAG_TEMPORARY_FAILURE_MASK | USH_DIAG_SERIOUS_FAILURE_MASK)

}tUSH_UsSensorDiag;

typedef enum _ttValidity
{
	VALID,
	INVALID

}tValidity;


typedef enum {
	GridRegionunknown = 0,
	GridRegionin,
	GridRegionout
}tUssGridRegion;

enum class FILEERR
{
	NOT_ERROR = 0,
	ERROR_FREAD,
	ERROR_FWRITE,

	MEM_ERROR,
};