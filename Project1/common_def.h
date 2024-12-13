#include "ultrasound_header.h"
#include "stdint.h"
#include <stdbool.h>

#define USH_US_SW_VER_LENGTH				(100U)	//��������汾���ַ�������
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
	tAPA_UltrasonicSts eUsSystemSts;			/** ����ϵͳ����״̬���� */
	uint16 u16SensorFailureBitMask;				/** ultrasonic sensors failure bit mask, 0: not failure, 1: failure*/
	tUSH_UsSupportScenes UsSupportScenes;		/** ����ϵͳ��ǰ֧�ֹ��� */
	tUSH_UsSysVersion sUsSysVersion;			/** ��������汾����Ϣ */
	tVehi_VehiType eVehiType;					/** �������䳵���ͺ� */
	uint8 reserved[1024];
} tUSH_UsSysInfo;