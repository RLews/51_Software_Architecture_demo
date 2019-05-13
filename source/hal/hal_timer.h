

#ifndef __HAL_TIMER_H
#define __HAL_TIMER_H

#include "drv_timer.h"
#include "hal_paltform.h"



void HalSysTimerInit(void);
uint32_t HalGetCurSysTimerCnt(void);
uint32_t HalDiffTimerCnt(uint32_t last);


#endif

