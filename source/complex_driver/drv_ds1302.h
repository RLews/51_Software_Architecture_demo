

#ifndef __DRV_DS1302_H
#define __DRV_DS1302_H

#include "drv_gpio.h"




void DrvDs1302Init(void);
void DrvDs1302BurstWrite(uint8_t dat[]);
void DrvDs1302BurstRead(uint8_t dat[]);


#endif

