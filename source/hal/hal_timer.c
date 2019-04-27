

#include "hal_timer.h"

#ifdef D_USE_ONEMS_INTRRUPET_MODE

static volatile uint32_t halSysTimerOverflowCnt = 0;

static void HalSysTimerInit(void);
static uint32_t HalGetCurSysTimerCnt(void);
static uint32_t HalDiffTimerCnt(uint32_t last);

D_SOFTWARE_INTERFACE halTimerInterface_t halTimerInterface = {
	HalSysTimerInit,
	HalGetCurSysTimerCnt,
	HalDiffTimerCnt
};


static void HalSysTimerInit(void)
{
	drvTimerInterface.SysTimerInit();
}

static uint32_t HalGetCurSysTimerCnt(void)
{
	uint32_t cnt = 0;
	bool_t sta = D_SYSTEM_ENTER_CRITICAL();
	
	cnt = halSysTimerOverflowCnt;
	D_SYSTEM_EXIT_CRITICAL(sta);

	return cnt;
}

static uint32_t HalDiffTimerCnt(uint32_t last)
{
	uint32_t tim = HalGetCurSysTimerCnt;

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
	drvTimerInterface.ReloadSysTimerCnt();
	halSysTimerOverflowCnt++;
}


#else
static volatile uint16_t halSysTimerOverflowCnt = 0;

static void HalSysTimerInit(void);
static uint16_t HalGetSysOverflowCnt(void);
static uint32_t HalGetCurSysTimerCnt(void);
static uint32_t HalDiffTimerCnt(uint32_t last);


D_SOFTWARE_INTERFACE halTimerInterface_t halTimerInterface = {
	HalSysTimerInit,
	HalGetCurSysTimerCnt,
	HalDiffTimerCnt
};


static void HalSysTimerInit(void)
{
	drvTimerInterface.SysTimerInit();
}

static uint16_t HalGetSysOverflowCnt(void)
{
	uint16_t cnt = 0;
	
	drvTimerInterface.DisableSysTimerInt();
	cnt = halSysTimerOverflowCnt;
	drvTimerInterface.EnableSysTimerInt();

	return cnt;
}


static uint32_t HalGetCurSysTimerCnt(void)
{
	uint32_t calcCnt = 0;
	uint16_t tOverflowCnt = 0;
	uint16_t tTimerCnt = 0;
	
	D_DISABLE_INTERRUPT();
	tTimerCnt = drvTimerInterface.GetSysTimerCnt();	/* maybe overflow */
	tOverflowCnt = HalGetSysOverflowCnt();
	if (drvTimerInterface.GetSysTimerOverflowFlag())
	{
		tTimerCnt = drvTimerInterface.GetSysTimerCnt();	
		tOverflowCnt++;
	}
	calcCnt = tTimerCnt;
	calcCnt |= (((uint32_t)tOverflowCnt) << 16);
	
	D_ENABLE_INTERRUPT();

	return calcCnt;
}

static uint32_t HalDiffTimerCnt(uint32_t last)
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
	drvTimerInterface.ReloadSysTimerCnt();
	halSysTimerOverflowCnt++;
}

#endif

