

#include "drv_gpio.h"




static const gpioConfig_t code gpioConfigArry[EN_ALL_GPIO_COUNTER] = {
	D_USED_GPIO_CONFIG
};





uint8_t Drv_SingleGpioIn(portGroup_t group, gpioBit_t bits)
{
	uint8_t inTtl = 0;
	
	switch (group)
	{
		case EN_PORT_0:
			if ( 0 != ( P0 & (0x01 << bits) ) )
			{
				inTtl = 1;
			}
			break;
			
		case EN_PORT_1:
			
			if ( 0 != ( P1 & (0x01 << bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		case EN_PORT_2:
			
			if ( 0 != ( P2 & (0x01 << bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		case EN_PORT_3:
			
			if ( 0 != ( P3 & (0x01 << bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		default:
			break;
	}
	return inTtl;
}

uint8_t Drv_GroupGpioIn(portGroup_t group)
{
	uint8_t inTtl = 0;
	
	switch (group)
	{
		case EN_PORT_0:
			inTtl = P0;
			break;
			
		case EN_PORT_1:
			inTtl = P1;
			
			break;
			
		case EN_PORT_2:
			inTtl = P2;
			
			break;
			
		case EN_PORT_3:
			inTtl = P3;
			
			break;
			
		default:
			break;
	}
	return inTtl;
}

void Drv_SingleGpioOut(portGroup_t group, gpioBit_t bits, uint8_t sig)
{
	switch (group)
	{
		case EN_PORT_0:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P0,bits);
			}
			else
			{
				D_BYTE_SET_BITS(P0,bits);
			}
			break;
			
		case EN_PORT_1:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P1,bits);
			}
			else
			{
				D_BYTE_SET_BITS(P1,bits);
			}
			break;
			
		case EN_PORT_2:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P2,bits);
			}
			else
			{
				D_BYTE_SET_BITS(P2,bits);
			}
			break;
			
		case EN_PORT_3:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P3,bits);
			}
			else
			{
				D_BYTE_SET_BITS(P3,bits);
			}
			break;
			
		default:
			break;
	}
}

void Drv_GroupGpioOut(portGroup_t group, uint8_t sig)
{
	
	switch (group)
	{
		case EN_PORT_0:
			P0 = sig;
			break;
			
		case EN_PORT_1:
			P1 = sig;
			break;
			
		case EN_PORT_2:
			P2 = sig;
			break;
			
		case EN_PORT_3:
			P3 = sig;
			break;
			
		default:
			break;
	}
}

void Drv_NameOut(gpioName_t name, uint8_t sig)
{

	if (gpioConfigArry[(uint8_t)name].gpioBit != EN_BIT_ALL)
	{
		Drv_SingleGpioOut(gpioConfigArry[(uint8_t)name].portGroup, gpioConfigArry[(uint8_t)name].gpioBit, sig);
	}
	else
	{
		Drv_GroupGpioOut(gpioConfigArry[(uint8_t)name].portGroup, sig);
	}
}

uint8_t Drv_NameIn(gpioName_t name)
{
	uint8_t inTtl = 0;
	
	if (gpioConfigArry[(uint8_t)name].gpioBit != EN_BIT_ALL)
	{
		inTtl = Drv_SingleGpioIn(gpioConfigArry[(uint8_t)name].portGroup, gpioConfigArry[(uint8_t)name].gpioBit);
	}
	else
	{
		inTtl = Drv_GroupGpioIn(gpioConfigArry[(uint8_t)name].portGroup);
	}

	return inTtl;
}



