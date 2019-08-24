

#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "drv_timer.h"
#include "hal_paltform.h"



void Hal_SysTimerInit(void);
uint32_t Hal_GetCurSysTimerCnt(void);
uint32_t Hal_DiffTimerCnt(uint32_t last);


#endif

