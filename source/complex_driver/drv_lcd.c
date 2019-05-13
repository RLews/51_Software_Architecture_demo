/*
		LCD1602�ײ����
*/

#include "drv_lcd.h"

static void DrvLcdWaitReady(void);



void DrvLcdInit(void)
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

	DrvNameOut(EN_LCD_DATA_BUS, 0xFF);
	DrvNameOut(EN_LCD_RS, 0);
	DrvNameOut(EN_LCD_RW, 1);
	
	do
	{
		DrvNameOut(EN_LCD_E, 1);
		sta = DrvNameIn(EN_LCD_DATA_BUS);
		DrvNameOut(EN_LCD_E, 0);
		tryCnt++;
	} while ((tryCnt < 10000) && (sta & 0x80)); //bit7 ���� 1 ��ʾҺ����æ���ظ����ֱ������� 0 Ϊֹ
}

void DrvLcdWriteCmd(uint8_t cmd)
{
	DrvLcdWaitReady();
	DrvNameOut(EN_LCD_RS, 0);
	DrvNameOut(EN_LCD_RW, 0);
	DrvNameOut(EN_LCD_DATA_BUS, cmd);
	DrvNameOut(EN_LCD_E, 1);
	DrvNameOut(EN_LCD_E, 0);
}

void DrvLcdWriteDat(uint8_t dat)
{
	DrvLcdWaitReady();
	DrvNameOut(EN_LCD_RS, 1);
	DrvNameOut(EN_LCD_RW, 0);
	DrvNameOut(EN_LCD_DATA_BUS, dat);
	DrvNameOut(EN_LCD_E, 1);
	DrvNameOut(EN_LCD_E, 0);
}


