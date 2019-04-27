

#ifndef __DRV_LCD_H
#define __DRV_LCD_H

#include "drv_gpio.h"

typedef struct _DRV_LCD_INTERFACE_T
{
	void (*LcdInit)(void);
	void (*LcdWriteCmd)(uint8_t cmd);
	void (*LcdWriteDat)(uint8_t dat);
}drvLcdInterface_t;

extern D_SOFTWARE_INTERFACE drvLcdInterface_t code drvLcdInterface;

#endif

