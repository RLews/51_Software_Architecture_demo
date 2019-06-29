

#include "hal_calendar.h"

static calendar_t sysCalendar = {
	0x2019, 0x05, 0x01, 0x12, 0x30, 0x20, 0x00
};





void Hal_CalendarInit(void)
{
	Drv_Ds1302Init();
}

void Hal_GetSysTime(calendar_t *pSysTmr)
{
	const calendar_t * pCalendar = &sysCalendar;

	pSysTmr->year = pCalendar->year;
	pSysTmr->mon = pCalendar->mon;
	pSysTmr->day = pCalendar->day;
	pSysTmr->hour = pCalendar->hour;
	pSysTmr->min = pCalendar->min;
	pSysTmr->sec = pCalendar->sec;
	pSysTmr->week = pCalendar->week;
}

void Hal_UpdateSysTime(void)
{
	uint8_t time[8] = {0};
	calendar_t * pCalendar = &sysCalendar;

	Drv_Ds1302BurstRead(time);
	pCalendar->year = time[6] + 0x2000;
	pCalendar->mon = time[4];
	pCalendar->day = time[3];
	pCalendar->hour = time[2];
	pCalendar->min = time[1];
	pCalendar->sec = time[0];
	pCalendar->week = time[5];
}



