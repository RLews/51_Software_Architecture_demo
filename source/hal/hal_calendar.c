

#include "hal_calendar.h"

static void HalCalendarInit(void);
static void HalUpdateSysTime(void);

calendar_t sysCalendar = {
	0x2019, 0x05, 0x01, 0x12, 0x30, 0x20, 0x00
};


D_SOFTWARE_INTERFACE halCalendarInterface_t halCalendarInterface = {
	HalCalendarInit,
	HalUpdateSysTime
};




static void HalCalendarInit(void)
{
	drvDs1302Interface.Ds1302Init();
}

static void HalUpdateSysTime(void)
{
	uint8_t time[8] = {0};
	calendar_t * pCalendar = &sysCalendar;

	drvDs1302Interface.Ds1302BurstRead(time);
	pCalendar->year = time[6] + 0x2000;
	pCalendar->mon = time[4];
	pCalendar->day = time[3];
	pCalendar->hour = time[2];
	pCalendar->min = time[1];
	pCalendar->sec = time[0];
	pCalendar->week = time[5];
}



