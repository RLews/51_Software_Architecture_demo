

#include "drv_ds1302.h"

static const uint8_t code initTimerDat[] = {0x00,0x30,0x12,0x20,0x10,0x07,0x13,0x00};

static void Drv_Ds1302ByteWrite(uint8_t dat);
static uint8_t Drv_Ds1302ByteRead(void);
static void Drv_Ds1302WriteReg(uint8_t reg, uint8_t dat);
static uint8_t Drv_Ds1302ReadReg(uint8_t reg);


void Drv_Ds1302Init(void)
{
	uint8_t dat = 0;
	
	Drv_NameOut(EN_DS1302_CE, 0);
	Drv_NameOut(EN_DS1302_CK, 0);
	dat = Drv_Ds1302ReadReg(0);
	if ( (dat & 0x80u) != 0 )
	{
		Drv_Ds1302WriteReg(7, 0x00);/* undo write protect */
		Drv_Ds1302BurstWrite(initTimerDat);
	}
}

static void Drv_Ds1302ByteWrite(uint8_t dat)
{
	uint8_t mask = 0;

	for (mask = 0x01; mask!=0; mask <<= 1u)
	{
		if ( (mask&dat) != 0 )
		{
			Drv_NameOut(EN_DS1302_IO, 1);
		}
		else
		{
			Drv_NameOut(EN_DS1302_IO, 0);
		}
		Drv_NameOut(EN_DS1302_CK, 1);
		Drv_NameOut(EN_DS1302_CK, 0);
	}
	
	Drv_NameOut(EN_DS1302_IO, 1);	//ÊÍ·ÅIO½Å
}

static uint8_t Drv_Ds1302ByteRead(void)
{
	uint8_t mask = 0;
	uint8_t dat = 0;

	for (mask = 0x01; mask != 0; mask <<= 1)
	{
		if (Drv_NameIn(EN_DS1302_IO) != 0)
		{
			dat |= mask;
		}
		Drv_NameOut(EN_DS1302_CK, 1);
		Drv_NameOut(EN_DS1302_CK, 0);
	}

	return dat;
}

static void Drv_Ds1302WriteReg(uint8_t reg, uint8_t dat)
{
	Drv_NameOut(EN_DS1302_CE, 1);
	Drv_Ds1302ByteWrite((reg << 1u) | 0x80u);		//·¢ËÍÐ´Ö¸Áî
	Drv_Ds1302ByteWrite(dat);
	Drv_NameOut(EN_DS1302_CE, 0);
}

static uint8_t Drv_Ds1302ReadReg(uint8_t reg)
{
	uint8_t dat = 0;
	
	Drv_NameOut(EN_DS1302_CE, 1);
	Drv_Ds1302ByteWrite((reg << 1u) | 0x81u);		//·¢ËÍ¶ÁÖ¸Áî
	dat = Drv_Ds1302ByteRead();
	Drv_NameOut(EN_DS1302_CE, 0);
	
	return dat;	
}

void Drv_Ds1302BurstWrite(const uint8_t dat[])
{
	uint8_t i = 0;

	Drv_NameOut(EN_DS1302_CE, 1);
	Drv_Ds1302ByteWrite(0xBE);		//·¢ËÍÍ»·¢Ð´¼Ä´æÆ÷Ö¸Áî
	
	for (i = 0; i < 8; i++)
	{
		Drv_Ds1302ByteWrite(dat[i]);
	}
	
	Drv_NameOut(EN_DS1302_CE, 0);
}

void Drv_Ds1302BurstRead(uint8_t dat[])
{
	uint8_t i = 0;
	
	Drv_NameOut(EN_DS1302_CE, 1);
	Drv_Ds1302ByteWrite(0xBF);
	
	for (i=0;i<8;i++)
	{
		dat[i] = Drv_Ds1302ByteRead();
	}
	
	Drv_NameOut(EN_DS1302_CE, 0);
}

