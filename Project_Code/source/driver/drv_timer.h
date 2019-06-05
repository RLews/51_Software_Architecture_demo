

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


#define D_DRV_ENABLE_SYSTIME_INT()		do { \
	ET0 = 1; \
}while (0)

#define D_DRV_DISABLE_SYSTIME_INT()		do { \
	ET0 = 0; \
}while (0)

#define D_DRV_ENABLE_SYSTIME()		do { \
	TR0 = 1; \
}while (0)

#define D_DRV_DISABLE_SYSTIME()		do { \
	TR0 = 0; \
}while (0)

#define D_DRV_RELOAD_SYSTIME_CNT()	do { \
	TH0 = D_SYSTEM_TIMER_TH_PADDING; \
	TL0 = D_SYSTEM_TIMER_TL_PADDING; \
}while (0)

#define D_DRV_GET_SYSTIME_INT_FLAG()	(TF0)

#define D_DRV_GET_SYSTIME_COUNT(count)		do { \
	D_DRV_DISABLE_SYSTIME_INT(); \
	count = TH0;                 \
	count = (uint16_t)(count << 8) + TL0;  \
	D_DRV_ENABLE_SYSTIME_INT();  \
}while (0)


void Drv_SysTimerInit(void);




#endif

