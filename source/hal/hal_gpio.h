

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H


#include "drv_gpio.h"

typedef struct _HAL_GPIO_INTERFACE_T
{
	void (*DebugIOCtrl)(uint8_t sig);
}halGpioInterface_t;

extern D_SOFTWARE_INTERFACE halGpioInterface_t code halGpioManage;

#endif

