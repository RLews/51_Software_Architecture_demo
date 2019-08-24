

#ifndef DRV_DS1302_H
#define DRV_DS1302_H

#include "drv_gpio.h"




void Drv_Ds1302Init(void);
void Drv_Ds1302BurstWrite(const uint8_t dat[]);
void Drv_Ds1302BurstRead(uint8_t dat[]);


#endif

