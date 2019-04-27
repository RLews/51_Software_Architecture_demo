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


static uint32_t sysTim = 0;
static bool_t ioCtrl = 0;

void main()
{

	bool_t sta = D_SYSTEM_ENTER_CRITICAL();
	halDisplayInterface.DisplayInit();
	halCalendarInterface.CalendarInit();
	halTimerInterface.TimerInit();
	D_SYSTEM_EXIT_CRITICAL(sta);
	
	sysTim = halTimerInterface.GetSysCnt();

	while(1)
	{
		if (halTimerInterface.DiffTimerCnt(sysTim) >= (uint32_t)D_SYS_TIME_100MS)
		{
			sysTim = halTimerInterface.GetSysCnt();
			halCalendarInterface.UpdateCalendar();
			halDisplayInterface.FlashCalendar();
			halGpioManage.DebugIOCtrl(ioCtrl);
			ioCtrl = (ioCtrl == 0)?(1):(0);
		}
	}
}



