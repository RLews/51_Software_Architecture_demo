

#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

/* 51 register headfile */
#include "drv_paltform.h"

#define D_BYTE_SET_BITS(byte, bits) do{ \
	(byte) |= (uint8_t)(1 << (bits)); \
}while(0)

#define D_BYTE_CLR_BITS(byte, bits) do{ \
	(byte) &= ~(uint8_t)(1 << (bits)); \
}while(0)

typedef enum __PORT_GROUP_T
{
	EN_PORT_0 = 0,
	EN_PORT_1,
	EN_PORT_2,
	EN_PORT_3
}portGroup_t;

typedef enum __GPIO_BIT_T
{
	EN_BIT_0 = 0,
    EN_BIT_1,
    EN_BIT_2,
    EN_BIT_3,
    EN_BIT_4,
    EN_BIT_5,
    EN_BIT_6,
    EN_BIT_7,
    EN_BIT_ALL
}gpioBit_t;

typedef enum __GPIO_NAME_T
{
	EN_DS1302_CE = 0,
	EN_DS1302_CK,
	EN_DS1302_IO,
	EN_LCD_DATA_BUS,
	EN_LCD_RS,
	EN_LCD_RW,
	EN_LCD_E,
	EN_DEBUG_IO,
	EN_ALL_GPIO_COUNTER
}gpioName_t;

typedef struct __GPIO_CONFIG_T
{
	gpioName_t name;
	portGroup_t portGroup;
	gpioBit_t gpioBit;
}gpioConfig_t;



#define D_USED_GPIO_CONFIG		\
	{EN_DS1302_CE, EN_PORT_1, EN_BIT_7}, \
	{EN_DS1302_CK, EN_PORT_1, EN_BIT_6}, \
	{EN_DS1302_IO, EN_PORT_3, EN_BIT_5}, \
	{EN_LCD_DATA_BUS, EN_PORT_0, EN_BIT_ALL}, \
	{EN_LCD_RS, EN_PORT_2, EN_BIT_5}, \
	{EN_LCD_RW, EN_PORT_2, EN_BIT_6}, \
	{EN_LCD_E, EN_PORT_2, EN_BIT_7}, \
	{EN_DEBUG_IO, EN_PORT_3, EN_BIT_0} 



uint8_t DrvSingleGpioIn(portGroup_t group, gpioBit_t bits);
uint8_t DrvGroupGpioIn(portGroup_t group);
void DrvSingleGpioOut(portGroup_t group, gpioBit_t bits, uint8_t sig);
void DrvGroupGpioOut(portGroup_t group, uint8_t sig);
void DrvNameOut(gpioName_t name, uint8_t sig);
uint8_t DrvNameIn(gpioName_t name);



#endif

