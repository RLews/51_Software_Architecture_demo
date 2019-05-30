

#ifndef __DRV_LCD_H
#define __DRV_LCD_H

#include "drv_gpio.h"


void Drv_LcdInit(void);
void Drv_LcdWriteCmd(uint8_t cmd);
void Drv_LcdWriteDat(uint8_t dat);


#endif

