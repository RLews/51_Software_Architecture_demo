

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


#include "drv_paltform.h"

//#define D_USE_ONEMS_INTRRUPET_MODE




void DrvSysTimerInit(void);
void DrvEnableSysTimerInt(void);
void DrvDisableSysTimerInt(void);
void DrvReloadSysTimerCnt(void);
uint16_t DrvGetSysTimerCnt(void);
uint8_t DrvGetSysTimerIntFlag(void);




#endif

