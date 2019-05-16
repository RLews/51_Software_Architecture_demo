/*
	万年历 —— V1.6
	基于V1.5版本
	引入全新架构
*/

#include "main.h"
#include "hal_paltform.h"
#include "hal_gpio.h"
#include "hal_timer.h"
#include "hal_display.h"
#include "hal_calendar.h"

#define D_SYS_ABSOLUTE_EXIT_CRITICAL			1

static void SysUpdateCalendar(void);
static void SysIoCtrl(void);


void main()
{

	(void)D_SYSTEM_ENTER_CRITICAL();
	HalDisplayInit();
	HalCalendarInit();
	HalSysTimerInit();
	D_SYSTEM_EXIT_CRITICAL(D_SYS_ABSOLUTE_EXIT_CRITICAL);

	while(1)
	{
		SysUpdateCalendar();
		
		SysIoCtrl();
	}
}

static void SysUpdateCalendar(void)
{
	static uint32_t updateTim = 0;

	if (HalDiffTimerCnt(updateTim) >= (uint32_t)D_SYS_TIME_10MS)
	{
		updateTim = HalGetCurSysTimerCnt();
		HalUpdateSysTime();
	}
	
	HalFlashCalendar();
}

static void SysIoCtrl(void)
{
	static uint32_t ctrlTim = 0;
	static bool_t ioCtrl = 0;

	if (HalDiffTimerCnt(ctrlTim) >= (uint32_t)D_SYS_TIME_100MS)
	{
		ctrlTim = HalGetCurSysTimerCnt();
		HalDebugIOCtrl(ioCtrl);
		ioCtrl = (ioCtrl == 0)?(1):(0);
	}
}


