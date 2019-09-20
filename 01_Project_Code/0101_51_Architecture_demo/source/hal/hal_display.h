

#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

#include "drv_lcd.h"
#include "hal_calendar.h"

typedef struct DISPLAY_COORDINATE_T
{
	uint8_t x;
	uint8_t y;
}DisplayCoordinate_t;

void Hal_DisplayInit(void);
void Hal_DisplayStr(uint8_t x, uint8_t y, const uint8_t *str);
void Hal_FlashCalendar(void);


#endif

