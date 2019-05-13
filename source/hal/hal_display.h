

#ifndef __HAL_DISPLAY_H
#define __HAL_DISPLAY_H

#include "drv_lcd.h"
#include "hal_calendar.h"

typedef struct __DISPLAY_COORDINATE_T
{
	uint8_t x;
	uint8_t y;
}displayCoordinate_t;

void HalDisplayInit(void);
void HalDisplayStr(uint8_t x, uint8_t y, const uint8_t *str);
void HalFlashCalendar(void);


#endif

