#pragma once
#include "common_def.h"
typedef struct
{
	tMsgMnger_ObjDetection sMsg_ObjDetection;/* '<Root>/sMsg_ObjDetection' */
	tMsgMnger_Freespace sMsg_UsFreespace;/* '<Root>/sMsg_UsFreespace' */
	tMsgMnger_PDC sMsg_PDC;            /* '<Root>/sMsg_PDC' */
	tUSH_UsSysInfo sUsSysInfo;         /* '<Root>/sUsSysInfo' */
	uint16 sUsDbgInfo[36];             /* '<Root>/sUsDbgInfo' */
	tSocUs_ObjDetection sSocUs_ObjDetection;/* '<Root>/sSocUs_ObjDetection' */
	tSocUs_Freespace sSocUs_Freespace; /* '<Root>/sSocUs_Freespace' */
	tSocUs_PDC sSocUs_PDC;             /* '<Root>/sSocUs_PDC' */
	tSocUs_UltrasonicPLD sSocUs_UltrasonicPLD;/* '<Root>/sSocUs_UltrasonicPLD' */
}
ExtY_ultrasonic_algo_T;
