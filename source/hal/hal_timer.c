

#include "hal_timer.h"

#ifdef D_USE_ONEMS_INTRRUPET_MODE

static volatile uint32_t halSysTimerOverflowCnt = 0;




void HalSysTimerInit(void)
{
	DrvSysTimerInit();
}

uint32_t HalGetCurSysTimerCnt(void)
{
	uint32_t cnt = 0;
	bool_t sta = D_SYSTEM_ENTER_CRITICAL();
	
	cnt = halSysTimerOverflowCnt;
	D_SYSTEM_EXIT_CRITICAL(sta);

	return cnt;
}

uint32_t HalDiffTimerCnt(uint32_t last)
{
	uint32_t tim = HalGetCurSysTimerCnt();

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


void HalSysTimerIsr()	interrupt	1
{
	DrvReloadSysTimerCnt();
	halSysTimerOverflowCnt++;
}


#else
static volatile uint16_t halSysTimerOverflowCnt = 0;

static uint16_t HalGetSysOverflowCnt(void);



void HalSysTimerInit(void)
{
	DrvSysTimerInit();
}

static uint16_t HalGetSysOverflowCnt(void)
{
	uint16_t cnt = 0;
	
	DrvDisableSysTimerInt();
	cnt = halSysTimerOverflowCnt;
	DrvEnableSysTimerInt();

	return cnt;
}


uint32_t HalGetCurSysTimerCnt(void)
{
	uint32_t calcCnt = 0;
	uint16_t tOverflowCnt = 0;
	uint16_t tTimerCnt = 0;
	
	D_DISABLE_INTERRUPT();
	tTimerCnt = DrvGetSysTimerCnt();	/* maybe overflow */
	tOverflowCnt = HalGetSysOverflowCnt();
	if (DrvGetSysTimerIntFlag())
	{
		tTimerCnt = DrvGetSysTimerCnt();	
		tOverflowCnt++;
	}
	calcCnt = tTimerCnt;
	calcCnt |= (((uint32_t)tOverflowCnt) << 16);
	
	D_ENABLE_INTERRUPT();

	return calcCnt;
}

uint32_t HalDiffTimerCnt(uint32_t last)
{
	uint32_t tim = 0;

	tim = HalGetCurSysTimerCnt();
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

void HalSysTimerIsr()	interrupt	1
{
	DrvReloadSysTimerCnt();
	halSysTimerOverflowCnt++;
}

#endif

