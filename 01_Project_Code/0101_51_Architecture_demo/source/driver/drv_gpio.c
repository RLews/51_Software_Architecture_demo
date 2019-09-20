

#include "drv_gpio.h"




static const GpioConfig_t code GpioConfigArry[EN_ALL_GPIO_COUNTER] = {
	D_USED_GPIO_CONFIG
};





uint8_t Drv_SingleGpioIn(PortGroup_t group, GpioBit_t bits)
{
	uint8_t inTtl = 0;
	
	switch (group)
	{
		case EN_PORT_0:
			if ( 0 != ( P0 & (0x01u << (uint8_t)bits) ) )
			{
				inTtl = 1;
			}
			break;
			
		case EN_PORT_1:
			
			if ( 0 != ( P1 & (0x01u << (uint8_t)bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		case EN_PORT_2:
			
			if ( 0 != ( P2 & (0x01u << (uint8_t)bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		case EN_PORT_3:
			
			if ( 0 != ( P3 & (0x01u << (uint8_t)bits) ) )
			{
				inTtl = 1;
			}
			
			break;
			
		default: //exception
			break;
	}
	return inTtl;
}

uint8_t Drv_GroupGpioIn(PortGroup_t group)
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
			
		default:   //exception
			break;
	}
	return inTtl;
}

void Drv_SingleGpioOut(PortGroup_t group, GpioBit_t bits, uint8_t sig)
{
	switch (group)
	{
		case EN_PORT_0:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P0,(uint8_t)bits);
			}
			else
			{
				D_BYTE_SET_BITS(P0,(uint8_t)bits);
			}
			break;
			
		case EN_PORT_1:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P1,(uint8_t)bits);
			}
			else
			{
				D_BYTE_SET_BITS(P1,(uint8_t)bits);
			}
			break;
			
		case EN_PORT_2:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P2,(uint8_t)bits);
			}
			else
			{
				D_BYTE_SET_BITS(P2,(uint8_t)bits);
			}
			break;
			
		case EN_PORT_3:
			if (sig == 0)
			{
				D_BYTE_CLR_BITS(P3,(uint8_t)bits);
			}
			else
			{
				D_BYTE_SET_BITS(P3,(uint8_t)bits);
			}
			break;
			
		default: //exception
			break;
	}
}

void Drv_GroupGpioOut(PortGroup_t group, uint8_t sig)
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
			
		default: //exception
			break;
	}
}

void Drv_NameOut(GpioName_t name, uint8_t sig)
{

	if (GpioConfigArry[(uint8_t)name].gpioBit != EN_BIT_ALL)
	{
		Drv_SingleGpioOut(GpioConfigArry[(uint8_t)name].portGroup, GpioConfigArry[(uint8_t)name].gpioBit, sig);
	}
	else
	{
		Drv_GroupGpioOut(GpioConfigArry[(uint8_t)name].portGroup, sig);
	}
}

uint8_t Drv_NameIn(GpioName_t name)
{
	uint8_t inTtl = 0;
	
	if (GpioConfigArry[(uint8_t)name].gpioBit != EN_BIT_ALL)
	{
		inTtl = Drv_SingleGpioIn(GpioConfigArry[(uint8_t)name].portGroup, GpioConfigArry[(uint8_t)name].gpioBit);
	}
	else
	{
		inTtl = Drv_GroupGpioIn(GpioConfigArry[(uint8_t)name].portGroup);
	}

	return inTtl;
}



