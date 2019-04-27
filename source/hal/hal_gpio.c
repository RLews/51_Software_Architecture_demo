

#include "hal_gpio.h"

static void HalDebugIOCtrl(uint8_t sig);

D_SOFTWARE_INTERFACE halGpioInterface_t code halGpioManage = {
	HalDebugIOCtrl
};


static void HalDebugIOCtrl(uint8_t sig)
{
	drvGpioInterface.NameOut(EN_DEBUG_IO, sig);
}

