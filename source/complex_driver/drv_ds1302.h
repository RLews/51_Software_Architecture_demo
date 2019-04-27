

#ifndef __DRV_DS1302_H
#define __DRV_DS1302_H

#include "drv_gpio.h"




typedef struct DRV_DS1302_INTERFACE_T
{
	void (*Ds1302Init)(void);
	void (*Ds1302BurstWrite)(uint8_t dat[]);
	void (*Ds1302BurstRead)(uint8_t dat[]);
}drvDs1302Interface_t;


extern D_SOFTWARE_INTERFACE drvDs1302Interface_t code drvDs1302Interface;

#endif

