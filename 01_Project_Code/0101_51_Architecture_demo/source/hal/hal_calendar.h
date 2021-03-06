

#ifndef HAL_CALENDAR_H
#define HAL_CALENDAR_H


#include "drv_ds1302.h"
#include "hal_display.h"

typedef struct 
{
	uint16_t year;
	uint8_t mon;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t week;
}Calendar_t;


void Hal_CalendarInit(void);
void Hal_UpdateSysTime(void);
void Hal_GetSysTime(Calendar_t *pSysTmr);


#endif

