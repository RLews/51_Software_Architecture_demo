

#ifndef __DRV_DS1302_H
#define __DRV_DS1302_H

#include "drv_gpio.h"




void Drv_Ds1302Init(void);
void Drv_Ds1302BurstWrite(uint8_t dat[]);
void Drv_Ds1302BurstRead(uint8_t dat[]);


#endif

