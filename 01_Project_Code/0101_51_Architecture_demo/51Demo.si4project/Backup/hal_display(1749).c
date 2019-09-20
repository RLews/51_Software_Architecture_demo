

#include "hal_display.h"


static void Hal_DisplayCalendar(const calendar_t * pCalendar);



void Hal_DisplayInit(void)
{
	Drv_LcdInit();
}

static void Hal_DisplayCalendar(const calendar_t * pCalendar)
{
	uint8_t str[11] = {0};
	
	str[0] = (uint8_t)'2';
	str[1] = (uint8_t)'0';
	str[2] = (uint8_t)(((pCalendar->year >> 4U) & 0x000FU) + (uint8_t)'0');//“年”高位数字转换为 ASCII 码
	str[3] = (uint8_t)((pCalendar->year & 0x000FU) + (uint8_t)'0');//“年”低位数字转换为 ASCII 码
	str[4] = (uint8_t)'-'; //添加日期分隔符
	str[5] = (uint8_t)((pCalendar->mon >> 4U) + (uint8_t)'0'); //“月”
	str[6] = (uint8_t)((pCalendar->mon & 0x0FU) + (uint8_t)'0');
	str[7] = (uint8_t)'-';
	str[8] = (uint8_t)((pCalendar->day >> 4U) + (uint8_t)'0'); //“日”
	str[9] = (uint8_t)((pCalendar->day & 0x0FU) + (uint8_t)'0');
	str[10] = (uint8_t)'\0';
	Hal_DisplayStr(0, 0, str); //显示到液晶的第一行

	str[0] = (uint8_t)((pCalendar->week & 0x0FU) + (uint8_t)'0'); //“星期”
	str[1] = (uint8_t)'\0';
	Hal_DisplayStr(11, 0, "week");
	Hal_DisplayStr(15, 0, str); //显示到液晶的第一行

	str[0] = (uint8_t)((pCalendar->hour >> 4U) + (uint8_t)'0'); //“时”
	str[1] = (uint8_t)((pCalendar->hour & 0x0FU) + (uint8_t)'0');
	str[2] = (uint8_t)':'; //添加时间分隔符
	str[3] = (uint8_t)((pCalendar->min >> 4U) + (uint8_t)'0'); //“分”
	str[4] = (uint8_t)((pCalendar->min & 0x0FU) + (uint8_t)'0');
	str[5] = (uint8_t)':';
	str[6] = (uint8_t)((pCalendar->sec >> 4U) + (uint8_t)'0'); //“秒”
	str[7] = (uint8_t)((pCalendar->sec & 0x0FU) + (uint8_t)'0');
	str[8] = (uint8_t)'\0';
	Hal_DisplayStr(4, 1, str); //显示到液晶的第二行
}

void Hal_FlashCalendar(void)
{
	static uint8_t secBak = 0;
	calendar_t tCalendar = {0};

	Hal_GetSysTime(&tCalendar);

	if (secBak != tCalendar.sec)
	{
		secBak = tCalendar.sec;
		Hal_DisplayCalendar(&tCalendar);
	}
}


void Hal_DisplayStr(uint8_t x, uint8_t y, const uint8_t *str)
{
	uint8_t addr = 0;
	//由输入的显示坐标计算显示 RAM 的地址
	if (y == 0)
	{
		addr = 0x00 + x; //第一行字符地址从 0x00 起始
	}
	else
	{
		addr = 0x40 + x; //第二行字符地址从 0x40 起始
	}
	//由起始显示 RAM 地址连续写入字符串
	Drv_LcdWriteCmd(addr | 0x80U); //写入起始地址
	while (*str != '\0') //连续写入字符串数据，直到检测到结束符
	{
		Drv_LcdWriteDat(*str);
		str++;
	}
}

