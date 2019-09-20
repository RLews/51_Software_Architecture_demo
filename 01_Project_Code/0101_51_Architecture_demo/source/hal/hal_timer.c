

#include "hal_timer.h"

#ifdef D_USE_ONEMS_INTRRUPET_MODE

static volatile uint32_t SysTimerOverflowCnt = 0;




void Hal_SysTimerInit(void)
{
	Drv_SysTimerInit();
}

uint32_t Hal_GetCurSysTimerCnt(void)
{
	uint32_t cnt = 0;
	D_DRV_DISABLE_SYSTIME_INT();
	
	cnt = SysTimerOverflowCnt;
	D_DRV_ENABLE_SYSTIME_INT();

	return cnt;
}

uint32_t Hal_DiffTimerCnt(uint32_t last)
{
	uint32_t tim = Hal_GetCurSysTimerCnt();

	if (tim >= last)
	{
		tim -= last;
	}
	else
	{
		tim += ((0xFFFFFFFFu - last) + 1);
	}

	return tim;
}


void Hal_SysTimerIsr(void)	interrupt	1
{
	D_DRV_RELOAD_SYSTIME_CNT();
	SysTimerOverflowCnt++;
}


#else
static volatile uint16_t SysTimerOverflowCnt = 0;

static uint16_t Hal_GetSysOverflowCnt(void);



void Hal_SysTimerInit(void)
{
	Drv_SysTimerInit();
}

static uint16_t Hal_GetSysOverflowCnt(void)
{
	uint16_t cnt = 0;
	
	D_DRV_DISABLE_SYSTIME_INT();
	cnt = SysTimerOverflowCnt;
	D_DRV_ENABLE_SYSTIME_INT();

	return cnt;
}


uint32_t Hal_GetCurSysTimerCnt(void)
{
	uint32_t calcCnt = 0;
	uint16_t tOverflowCnt = 0;
	uint16_t tTimerCnt = 0;
	
	D_DISABLE_INTERRUPT();
	D_DRV_GET_SYSTIME_COUNT(tTimerCnt);	/* maybe overflow */
	tOverflowCnt = Hal_GetSysOverflowCnt();
	if (D_DRV_GET_SYSTIME_INT_FLAG())
	{
		D_DRV_GET_SYSTIME_COUNT(tTimerCnt);	
		tOverflowCnt++;
	}
	calcCnt = tTimerCnt;
	calcCnt |= (((uint32_t)tOverflowCnt) << 16);
	
	D_ENABLE_INTERRUPT();

	return calcCnt;
}

uint32_t Hal_DiffTimerCnt(uint32_t last)
{
	uint32_t tim = 0;

	tim = Hal_GetCurSysTimerCnt();
	if (tim >= last)
	{
		tim -= last;
	}
	else
	{
		tim += ((0xFFFFFFFFu - last) + 1);
	}

	return tim;
}

void Hal_SysTimerIsr(void)	interrupt	1
{
	D_DRV_RELOAD_SYSTIME_CNT();
	SysTimerOverflowCnt++;
}

#endif

