

#ifndef __HAL_TIMER_H
#define __HAL_TIMER_H

#include "drv_timer.h"
#include "hal_paltform.h"


typedef struct _HAL_TIMER_INTERFACE_T
{
	void (*TimerInit)(void);
	uint32_t (*GetSysCnt)(void);
	uint32_t (*DiffTimerCnt)(uint32_t last);
}halTimerInterface_t;

extern D_SOFTWARE_INTERFACE halTimerInterface_t halTimerInterface;


#endif

