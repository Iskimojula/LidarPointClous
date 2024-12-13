#include "ultrasound_header.h"
#include "stdint.h"
#include <stdbool.h>

#define USH_US_SW_VER_LENGTH				(100U)	//超声软件版本号字符串长度
typedef struct USH_UsSysVersion
{
	uint8 VersionInfo[USH_US_SW_VER_LENGTH];	/** software version string */
} tUSH_UsSysVersion;
typedef struct USH_UsSupportScenes
{
	tSupportSts UsSupportPdc;					/** Support PDC */
	tSupportSts UsSupportApaSearching;			/** Support APA_STS_SEARCHING */
	tSupportSts UsSupportApaActive;				/** Support APA_STS_ACTIVE */
} tUSH_UsSupportScenes;
typedef struct USH_UsSysInfo
{
	TimestampType u64Timestamp_us;
	tAPA_UltrasonicSts eUsSystemSts;			/** 超声系统工作状态反馈 */
	uint16 u16SensorFailureBitMask;				/** ultrasonic sensors failure bit mask, 0: not failure, 1: failure*/
	tUSH_UsSupportScenes UsSupportScenes;		/** 超声系统当前支持工况 */
	tUSH_UsSysVersion sUsSysVersion;			/** 超声软件版本号信息 */
	tVehi_VehiType eVehiType;					/** 超声适配车辆型号 */
	uint8 reserved[1024];
} tUSH_UsSysInfo;