

#include "hal_gpio.h"



void Hal_DebugIOCtrl(uint8_t sig)
{
	Drv_NameOut(EN_DEBUG_IO, sig);
}

