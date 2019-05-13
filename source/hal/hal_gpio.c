

#include "hal_gpio.h"



void HalDebugIOCtrl(uint8_t sig)
{
	DrvNameOut(EN_DEBUG_IO, sig);
}

