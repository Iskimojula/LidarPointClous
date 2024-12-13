#pragma once
#include "ultrasound_enum.h"

typedef struct _tObjProperty2D
{
	TimestampType u64Timestamp_us;
	tAPA_ObjType eType;  // object type
	float32_t f32X;  // unit: m
	float32_t f32Y;  // unit: m
	float32_t f32Theta;  // unit: rad (-pi, pi]
	float32_t f32Width;  // unit: m
	float32_t f32Depth;  // unit: m
	uint16_t u16Id;  // object identifier (0=invalid ID)
	uint8_t u8Confidence;  // object confidence
	uint8_t u8res;

}tObjProperty2D;

typedef struct _tMsgMnger_ObjDetection
{
	TimestampType u64Timestamp_us;
	tAPA_FunctionSts eObjectDetectionSts;
	tObjProperty2D sObjProperty2D[OD_NUM_MAX];
	uint8 reserved[64U];

}tMsgMnger_ObjDetection;



typedef struct _tMsgMnger_FsBoundary
{
	float32_t f32XY[2];
	PixelLabel eLabel;

}tMsgMnger_FsBoundary;


typedef struct _tMsgMnger_Freespace
{
	TimestampType u64Timestamp_us;
	tAPA_FunctionSts eApaFreespaceSts;
	tMsgMnger_FsBoundary sFsBoundary[FS_BOUND_NUM_MAX];

}tMsgMnger_Freespace;

typedef struct _tUSH_DistanceCell
{
	uint16 u16Distance_cm;  /* ultrasonic distance£¬unit: (cm). */
	uint8 u8Confidence;  /* confidence of distance. */
	uint8 u8Reserved;

}tUSH_DistanceCell;
typedef struct _tUSH_Peb92Distance
{
	tUSH_DistanceCell sDistanceCell[2U];  /* PEB92 distance cell collection. */

}tUSH_Peb92Distance;

typedef struct _tMsgMnger_PDC
{
	TimestampType u64Timestamp_us;
	tAPA_UltrasonicSts eApaPdcSts;  /* Ultrasonic PDC/PEB status. */
	uint16 u16Distance[US_IDX_NUM_MAX];  /* PDC12 distance of front zone (8~11); rear zone (4~7); side zone (0~3), unit: (cm). */
	uint16 u16PdcDistance[PDC_ZONE_NUM];  /* PEB20 distance of front zone (0~7); rear zone (8~15); side zone (16~19); unit: (cm). */
	uint16 u16SensorFailureBitMask;  /* 12 ultrasonic sensors(bit0~11) failure bit mask, 0: not failure, 1: failure */
	uint16 u16BlindZoneLockStsBitMask;  /* PEB06 blind zone(Front/Rear/FRS/RRS/FLS/RLS) lock status bit mask , 0: unlocked, 1: locked. */
	tPDC_AudioWarnLv ePdcAudioWarnLv[6U];  /* PDC06 audio warning level. (Front/Rear/FRS/RRS/FLS/RLS) */
	tUSH_Peb92Distance sPeb92Distance[PEB_ZONE_NUM];  /* PEB92 distance of front zone (0~35); rear zone (36~71); side zone (RS=72~81,LS=82~91); unit: (cm). */
	sint16 s16Meb100Distance_cm[MEB_ZONE_NUM];  /* MEB100 distance of front zone (0~39); rear zone (40~79); side zone (RS=80~89,LS=90~99); unit: (cm). */
	uint16 u16Peb04DistanceFrlr_cm[4U];  /* PEB04 distance 4 zone. (Front/Rear/Left/Right) */
	uint16 u16Pdc04DistanceFrlr_cm[4U];  /* PDC04 distance 4 zone. (Front/Rear/Left/Right) */
	uint16 u16Pdc20RectangleDistance_cm[50U];  /* PDC20 rectangle zone distance. */
	uint8 u8Reserved[372U];

}tMsgMnger_PDC;

typedef struct _tSocUs_ObjDetection
{
	TimestampType u64Timestamp_us;
	tAPA_FunctionSts eObjectDetectionSts;
	tObjProperty2D sObjProperty2D[SOC_US_OD_NUM_MAX];
	uint8 reserved[1024];

}tSocUs_ObjDetection;

typedef struct _tSocUs_Freespace
{
	TimestampType u64Timestamp_us;
	tAPA_FunctionSts eApaFreespaceSts;
	tMsgMnger_FsBoundary sFsBoundary[SOC_US_FS_BOUND_NUM_MAX];
	uint8 reserved[4096];

}tSocUs_Freespace;

typedef struct _tSocUs_PDC
{
	TimestampType u64Timestamp_us;
	tAPA_UltrasonicSts eApaPdcSts;  // ³¬ÉùPDC×´Ì¬·´À¡
	uint16 u16Distance[US_IDX_NUM_MAX];  // distance of sensor detected first obstacle, unit: (cm).
	uint16 u16PdcDistance[SOC_US_PDC_ZONE_NUM];  // distance of front zone * 8; rear zone * 8; side zone * 4; unit: (cm).
	uint16 u16SensorFailureBitMask;  // ultrasonic sensors failure bit mask, 0: not failure, 1: failure
	uint8 reserved[2];
	uint8 reserved1[512];

}tSocUs_PDC;
typedef struct _tMsgMnger_PldInfo
{
	tObjProperty2D sObjProperty2D;
	tAPA_PldBerthAvailable ePldBerthAvailable;  // berth available status

}tMsgMnger_PldInfo;
typedef struct _tSocUs_UltrasonicPLD
{
	TimestampType u64Timestamp_us;
	tAPA_UlrasonicPldSts eApaUltrasonicPldSts;
	tMsgMnger_PldInfo sUpldInfo[SOC_US_PLD_NUM_MAX_UPLD];  // ultrasonic PLD information
	uint8 reserved[256];

}tSocUs_UltrasonicPLD;


typedef struct _tObjProperty3D
{
	TimestampType u64Timestamp_us;
	tAPA_ObjType eType;  // object type
	float32_t f32X;  // unit: m
	float32_t f32Y;  // unit: m
	float32_t f32Z;  // unit: m
	float32_t f32Yaw;  // unit: rad (-pi, pi]
	float32_t f32Pitch;  // unit: rad (-pi, pi]
	float32_t f32Roll;  // unit: rad (-pi, pi]
	float32_t f32Width;  // unit: m
	float32_t f32Depth;  // unit: m
	float32_t f32Height;  // unit: m
	uint16_t u16Id;  // object identifier (0=invalid ID)
	uint8_t u8Confidence;  // object confidence
	uint8_t u8res;

}tObjProperty3D;


typedef struct _tUSH_ObstacleInfo
{
	TimestampType u64Timestamp_us;
	tUSH_UsIdx eSendUsIdx;  // sensor which transmits ultrasonic signal
	tUSH_UsIdx eRecvUsIdx;  // sensor which receive ultrasonic signal
	uint16 u16Length[USH_ECHO_NUM_MAX];  // total length of ultrasonic path, unit: (mm).
	uint16 u16Width[USH_ECHO_NUM_MAX];  // unit: (us).
	uint8 u8EchoHeight[USH_ECHO_NUM_MAX];  // the echo height of the echo (0~0x3F)
	uint8 u8EchoNum;  // number of echoes (0~5)
	uint8 u8RollingCount;  // obstacle information updated rolling counter (0~255)
	uint8 u8res;
	tUSH_MeasurementProfile eMeasProf;  // sensor measurement profile
	tUSH_UsExtendSts eUsExtendSts;  // ultrasonic service extend status mask
	tUSH_UsSensorDiag eUsDiagSts;  // sensor diagnostic result

}tUSH_ObstacleInfo;



typedef struct _tMsgMnger_UsObstacle
{
	TimestampType u64Timestamp_us;
	tAPA_UltrasonicSts eUsObstacleFuncSts;
	uint16 u16SensorFailureBitMask;  // ultrasonic sensors failure bit mask, 0: not failure, 1: failure
	uint16 u16BlindZoneUnlockTriggerBitMask;  // (Front/Rear/FRS/RRS/FLS/RLS)
	tUSH_ObstacleInfo sObstacleInfo[US_IDX_NUM_MAX * USH_ONE_SND_MULT_RCV_MAX];
	uint8 u8RollingCountApa;  // all APA information updated rolling counter (0~255)
	uint8 u8RollingCountPdc;  // all PDC information updated rolling counter (0~255)
	uint16 u16SendSensorUpdateBitMask;  // 0~11 bit correspond to 12 sensor; 0=no update, 1=updated; (cycle=50ms)
	tUSH_Temperature_degC fEnvironmentTemperature;
	tUSH_Temperature_degC fUsSensorTemperature;

}tMsgMnger_UsObstacle;


typedef struct _ST_VEHICLE_VCU_INFO
{
	tVehiGear eVehicleGear;  // vehicle gear
	tActiveSts eBrakeActiveSts;  // brake active status

}ST_VEHICLE_VCU_INFO, *PST_VEHICLE_VCU_INFO;



typedef struct _ST_VEHICLE_EPS_INFO
{
	float32_t f32SteeringWheelAngle;  // (deg)
	float32_t f32SteeringWheelAngleSpd;  // (deg/s)

}ST_VEHICLE_EPS_INFO, *PST_VEHICLE_EPS_INFO;


typedef struct _ST_VEHICLE_ESC_INFO
{
	tValidity eVehicleSpeedValidity;  // vehicle speed validity
	float32_t f32VehicleSpeed;  // vehicle speed, (kph)
	float32_t f32WheelSpeedFL;  // left front wheel speed (kph)
	float32_t f32WheelSpeedFR;  // right front wheel speed (kph)
	float32_t f32WheelSpeedRL;  // left rear wheel speed (kph)
	float32_t f32WheelSpeedRR;  // right rear wheel speed (kph)
	uint16_t u16WheSpePulFL;  // left front wheel pulse
	uint16_t u16WheSpePulFR;  // right front wheel pulse
	uint16_t u16WheSpePulRL;  // left rear wheel pulse
	uint16_t u16WheSpePulRR;  // right rear wheel pulse
	tWheelDirection eWheelDirFL;  // left front wheel direction
	tWheelDirection eWheelDirFR;  // right front wheel direction
	tWheelDirection eWheelDirRL;  // left rear wheel direction
	tWheelDirection eWheelDirRR;  // right rear wheel direction
	uint8_t u8VehStantStill;
	uint8_t u8Res[7];

}ST_VEHICLE_ESC_INFO, *PST_VEHICLE_ESC_INFO;



typedef struct _tVehi_VehicleDataRx
{
	uint64_t u64Timestamp_us;
	ST_VEHICLE_VCU_INFO stVehVCUInfo;  // vehilce VCU info
	ST_VEHICLE_EPS_INFO stVehEPSInfo;  // vehilce EPS info
	ST_VEHICLE_ESC_INFO stVehESCInfo;  // vehilce ESC info
	float32_t ambientAirTemp_degC;  // ambient air temperature, (degC)
	tValidity ambientAirTempValidity;  // ambient air validity
	uint8_t u8Res[8];

}tVehi_VehicleDataRx, *pst_tVehicleDataRx_T;



typedef struct _tMsgMnger_VehicleInfo
{
	TimestampType u64Timestamp_us;
	int32_t eVehiType;  // vehicle type, NL5/MCE/etc...
	tVehi_VehicleDataRx sVehicleDataRx;  // received vehicle CAN data

}tMsgMnger_VehicleInfo;


typedef struct
{
	TimestampType u64Timestamp_us;     /* '<Root>/u64Timestamp_us' */
	tObjProperty3D sVehiLocalization;  /* '<Root>/sVehiLocalization' */
	tMsgMnger_UsObstacle sObstacleInfoAll;/* '<Root>/sObstacleInfoAll' */
	tMsgMnger_Freespace sMsg_VsFreespace;/* '<Root>/sMsg_VsFreespace' */
	tMsgMnger_VehicleInfo sVehiInfo;   /* '<Root>/sVehiInfo' */
}
ExtU_ultrasonic_algo_T;

