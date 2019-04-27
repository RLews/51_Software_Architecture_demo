

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


#include "drv_paltform.h"

#define D_USE_ONEMS_INTRRUPET_MODE



typedef struct _DRV_TIMER_INTERFACE_T
{
	void (*SysTimerInit)(void);
	void (*EnableSysTimerInt)(void);
	void (*DisableSysTimerInt)(void);
	void (*ReloadSysTimerCnt)(void);
	uint16_t (*GetSysTimerCnt)(void);
	uint8_t (*GetSysTimerOverflowFlag)(void);
}drvTimerInterface_t;


extern D_SOFTWARE_INTERFACE drvTimerInterface_t drvTimerInterface;





#endif

