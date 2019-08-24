/*
		LCD1602底层程序
*/

#include "drv_lcd.h"

static void Drv_LcdWaitReady(void);



void Drv_LcdInit(void)
{
	Drv_LcdWriteCmd(0x38); //16*2 显示，5*7 点阵，8 位数据接口
	Drv_LcdWriteCmd(0x0C); //显示器开，光标关闭
	Drv_LcdWriteCmd(0x06); //文字不动，地址自动+1
	Drv_LcdWriteCmd(0x01); //清屏
}

static void Drv_LcdWaitReady(void)
{
	uint8_t sta = 0;
	uint16_t tryCnt = 0;

	Drv_NameOut(EN_LCD_DATA_BUS, 0xFF);
	Drv_NameOut(EN_LCD_RS, 0);
	Drv_NameOut(EN_LCD_RW, 1);
	
	do
	{
		Drv_NameOut(EN_LCD_E, 1);
		sta = Drv_NameIn(EN_LCD_DATA_BUS);
		Drv_NameOut(EN_LCD_E, 0);
		tryCnt++;
	} while ((tryCnt < 10000UL) && (0 != (sta & 0x80U))); //bit7 等于 1 表示液晶正忙，重复检测直到其等于 0 为止
}

void Drv_LcdWriteCmd(uint8_t cmd)
{
	Drv_LcdWaitReady();
	Drv_NameOut(EN_LCD_RS, 0);
	Drv_NameOut(EN_LCD_RW, 0);
	Drv_NameOut(EN_LCD_DATA_BUS, cmd);
	Drv_NameOut(EN_LCD_E, 1);
	Drv_NameOut(EN_LCD_E, 0);
}

void Drv_LcdWriteDat(uint8_t dat)
{
	Drv_LcdWaitReady();
	Drv_NameOut(EN_LCD_RS, 1);
	Drv_NameOut(EN_LCD_RW, 0);
	Drv_NameOut(EN_LCD_DATA_BUS, dat);
	Drv_NameOut(EN_LCD_E, 1);
	Drv_NameOut(EN_LCD_E, 0);
}


