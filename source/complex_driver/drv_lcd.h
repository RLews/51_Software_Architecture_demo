

#ifndef __DRV_LCD_H
#define __DRV_LCD_H

#include "drv_gpio.h"


void DrvLcdInit(void);
void DrvLcdWriteCmd(uint8_t cmd);
void DrvLcdWriteDat(uint8_t dat);


#endif

