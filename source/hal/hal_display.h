

#ifndef __HAL_DISPLAY_H
#define __HAL_DISPLAY_H

#include "drv_lcd.h"
#include "hal_calendar.h"

typedef struct __DISPLAY_COORDINATE_T
{
	uint8_t x;
	uint8_t y;
}displayCoordinate_t;

typedef struct __HAL_DISPLAY_INTERFACE_T
{
	void (*DisplayInit)(void);
	void (*DisplayStr)(uint8_t x, uint8_t y, const uint8_t *str);
	void (*FlashCalendar)(void);
}halDisplayInterface_t;

extern D_SOFTWARE_INTERFACE halDisplayInterface_t halDisplayInterface;

#endif

