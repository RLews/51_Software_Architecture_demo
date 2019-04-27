/*
		LCD1602�ײ����
*/

#include "drv_lcd.h"

static void DrvLcdInit(void);
static void DrvLcdWaitReady(void);
static void DrvLcdWriteCmd(uint8_t cmd);
static void DrvLcdWriteDat(uint8_t dat);


D_SOFTWARE_INTERFACE drvLcdInterface_t code drvLcdInterface = {
	DrvLcdInit,
	DrvLcdWriteCmd,
	DrvLcdWriteDat
};


static void DrvLcdInit(void)
{
	DrvLcdWriteCmd(0x38); //16*2 ��ʾ��5*7 ����8 λ���ݽӿ�
	DrvLcdWriteCmd(0x0C); //��ʾ���������ر�
	DrvLcdWriteCmd(0x06); //���ֲ�������ַ�Զ�+1
	DrvLcdWriteCmd(0x01); //����
}

static void DrvLcdWaitReady(void)
{
	uint8_t sta = 0;
	uint16_t tryCnt = 0;

	drvGpioInterface.NameOut(EN_LCD_DATA_BUS, 0xFF);
	drvGpioInterface.NameOut(EN_LCD_RS, 0);
	drvGpioInterface.NameOut(EN_LCD_RW, 1);
	
	do
	{
		drvGpioInterface.NameOut(EN_LCD_E, 1);
		sta = drvGpioInterface.NameIn(EN_LCD_DATA_BUS);
		drvGpioInterface.NameOut(EN_LCD_E, 0);
		tryCnt++;
	} while ((tryCnt < 10000) && (sta & 0x80)); //bit7 ���� 1 ��ʾҺ����æ���ظ����ֱ������� 0 Ϊֹ
}

static void DrvLcdWriteCmd(uint8_t cmd)
{
	DrvLcdWaitReady();
	drvGpioInterface.NameOut(EN_LCD_RS, 0);
	drvGpioInterface.NameOut(EN_LCD_RW, 0);
	drvGpioInterface.NameOut(EN_LCD_DATA_BUS, cmd);
	drvGpioInterface.NameOut(EN_LCD_E, 1);
	drvGpioInterface.NameOut(EN_LCD_E, 0);
}

static void DrvLcdWriteDat(uint8_t dat)
{
	DrvLcdWaitReady();
	drvGpioInterface.NameOut(EN_LCD_RS, 1);
	drvGpioInterface.NameOut(EN_LCD_RW, 0);
	drvGpioInterface.NameOut(EN_LCD_DATA_BUS, dat);
	drvGpioInterface.NameOut(EN_LCD_E, 1);
	drvGpioInterface.NameOut(EN_LCD_E, 0);
}


