

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


#include "drv_paltform.h"

#define D_USE_ONEMS_INTRRUPET_MODE

#ifdef D_USE_ONEMS_INTRRUPET_MODE
#define D_SYSTEM_TIMER_TH_PADDING		(0xFCu)
#define D_SYSTEM_TIMER_TL_PADDING		(0x92u)
#else
#define D_SYSTEM_TIMER_TH_PADDING		(0x00u)
#define D_SYSTEM_TIMER_TL_PADDING		(0x00u)
#endif

void DrvSysTimerInit(void);
void DrvEnableSysTimerInt(void);
void DrvDisableSysTimerInt(void);
void DrvReloadSysTimerCnt(void);
uint16_t DrvGetSysTimerCnt(void);
uint8_t DrvGetSysTimerIntFlag(void);




#endif

