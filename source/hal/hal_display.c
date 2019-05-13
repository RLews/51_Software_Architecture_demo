

#include "hal_display.h"

extern calendar_t sysCalendar;


static void HalDisplayCalendar(const calendar_t * pCalendar);



void HalDisplayInit(void)
{
	DrvLcdInit();
}

static void HalDisplayCalendar(const calendar_t * pCalendar)
{
	uint8_t str[11] = {0};
	
	str[0] = '2';
	str[1] = '0';
	str[2] = ((pCalendar->year >> 4) & 0x000F) + '0';//“年”高位数字转换为 ASCII 码
	str[3] = (pCalendar->year & 0x000F) + '0';//“年”低位数字转换为 ASCII 码
	str[4] = '-'; //添加日期分隔符
	str[5] = (pCalendar->mon >> 4) + '0'; //“月”
	str[6] = (pCalendar->mon & 0x0F) + '0';
	str[7] = '-';
	str[8] = (pCalendar->day >> 4) + '0'; //“日”
	str[9] = (pCalendar->day & 0x0F) + '0';
	str[10] = '\0';
	HalDisplayStr(0, 0, str); //显示到液晶的第一行

	str[0] = (pCalendar->week & 0x0F) + '0'; //“星期”
	str[1] = '\0';
	HalDisplayStr(11, 0, "week");
	HalDisplayStr(15, 0, str); //显示到液晶的第一行

	str[0] = (pCalendar->hour >> 4) + '0'; //“时”
	str[1] = (pCalendar->hour & 0x0F) + '0';
	str[2] = ':'; //添加时间分隔符
	str[3] = (pCalendar->min >> 4) + '0'; //“分”
	str[4] = (pCalendar->min & 0x0F) + '0';
	str[5] = ':';
	str[6] = (pCalendar->sec >> 4) + '0'; //“秒”
	str[7] = (pCalendar->sec & 0x0F) + '0';
	str[8] = '\0';
	HalDisplayStr(4, 1, str); //显示到液晶的第二行
}

void HalFlashCalendar(void)
{
	static uint8_t secBak = 0;
	calendar_t tCalendar = {0};

	HalGetSysTime(&tCalendar);

	if (secBak != tCalendar.sec)
	{
		secBak = tCalendar.sec;
		HalDisplayCalendar(&tCalendar);
	}
}


void HalDisplayStr(uint8_t x, uint8_t y, const uint8_t *str)
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
	DrvLcdWriteCmd(addr | 0x80); //写入起始地址
	while (*str != '\0') //连续写入字符串数据，直到检测到结束符
	{
		DrvLcdWriteDat(*str);
		str++;
	}
}

