

#include "drv_ds1302.h"

static const uint8_t code initTimerDat[] = {0x00,0x30,0x12,0x20,0x10,0x07,0x13,0x00};

static void DrvDs1302ByteWrite(uint8_t dat);
static uint8_t DrvDs1302ByteRead(void);
static void DrvDs1302WriteReg(uint8_t reg, uint8_t dat);
static uint8_t DrvDs1302ReadReg(uint8_t reg);


void DrvDs1302Init(void)
{
	uint8_t dat = 0;
	
	DrvNameOut(EN_DS1302_CE, 0);
	DrvNameOut(EN_DS1302_CK, 0);
	dat = DrvDs1302ReadReg(0);
	if ( (dat & 0x80) != 0 )
	{
		DrvDs1302WriteReg(7, 0x00);/* undo write protect */
		DrvDs1302BurstWrite(initTimerDat);
	}
}

static void DrvDs1302ByteWrite(uint8_t dat)
{
	uint8_t mask = 0;

	for (mask = 0x01; mask!=0; mask <<= 1)
	{
		if ( (mask&dat) != 0 )
		{
			DrvNameOut(EN_DS1302_IO, 1);
		}
		else
		{
			DrvNameOut(EN_DS1302_IO, 0);
		}
		DrvNameOut(EN_DS1302_CK, 1);
		DrvNameOut(EN_DS1302_CK, 0);
	}
	
	DrvNameOut(EN_DS1302_IO, 1);	//�ͷ�IO��
}

static uint8_t DrvDs1302ByteRead(void)
{
	uint8_t mask = 0;
	uint8_t dat = 0;

	for (mask = 0x01; mask != 0; mask <<= 1)
	{
		if (DrvNameIn(EN_DS1302_IO) != 0)
		{
			dat |= mask;
		}
		DrvNameOut(EN_DS1302_CK, 1);
		DrvNameOut(EN_DS1302_CK, 0);
	}

	return dat;
}

static void DrvDs1302WriteReg(uint8_t reg, uint8_t dat)
{
	DrvNameOut(EN_DS1302_CE, 1);
	DrvDs1302ByteWrite((reg<<1) | 0x80);		//����дָ��
	DrvDs1302ByteWrite(dat);
	DrvNameOut(EN_DS1302_CE, 0);
}

static uint8_t DrvDs1302ReadReg(uint8_t reg)
{
	uint8_t dat = 0;
	
	DrvNameOut(EN_DS1302_CE, 1);
	DrvDs1302ByteWrite((reg<<1) | 0x81);		//���Ͷ�ָ��
	dat = DrvDs1302ByteRead();
	DrvNameOut(EN_DS1302_CE, 0);
	
	return dat;	
}

void DrvDs1302BurstWrite(uint8_t dat[])
{
	uint8_t i = 0;

	DrvNameOut(EN_DS1302_CE, 1);
	DrvDs1302ByteWrite(0xBE);		//����ͻ��д�Ĵ���ָ��
	
	for (i = 0; i < 8; i++)
	{
		DrvDs1302ByteWrite(dat[i]);
	}
	
	DrvNameOut(EN_DS1302_CE, 0);
}

void DrvDs1302BurstRead(uint8_t dat[])
{
	uint8_t i = 0;
	
	DrvNameOut(EN_DS1302_CE, 1);
	DrvDs1302ByteWrite(0xBF);
	
	for (i=0;i<8;i++)
	{
		dat[i] = DrvDs1302ByteRead();
	}
	
	DrvNameOut(EN_DS1302_CE, 0);
}

