

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
	str[2] = ((pCalendar->year >> 4) & 0x000F) + '0';//���ꡱ��λ����ת��Ϊ ASCII ��
	str[3] = (pCalendar->year & 0x000F) + '0';//���ꡱ��λ����ת��Ϊ ASCII ��
	str[4] = '-'; //������ڷָ���
	str[5] = (pCalendar->mon >> 4) + '0'; //���¡�
	str[6] = (pCalendar->mon & 0x0F) + '0';
	str[7] = '-';
	str[8] = (pCalendar->day >> 4) + '0'; //���ա�
	str[9] = (pCalendar->day & 0x0F) + '0';
	str[10] = '\0';
	HalDisplayStr(0, 0, str); //��ʾ��Һ���ĵ�һ��

	str[0] = (pCalendar->week & 0x0F) + '0'; //�����ڡ�
	str[1] = '\0';
	HalDisplayStr(11, 0, "week");
	HalDisplayStr(15, 0, str); //��ʾ��Һ���ĵ�һ��

	str[0] = (pCalendar->hour >> 4) + '0'; //��ʱ��
	str[1] = (pCalendar->hour & 0x0F) + '0';
	str[2] = ':'; //���ʱ��ָ���
	str[3] = (pCalendar->min >> 4) + '0'; //���֡�
	str[4] = (pCalendar->min & 0x0F) + '0';
	str[5] = ':';
	str[6] = (pCalendar->sec >> 4) + '0'; //���롱
	str[7] = (pCalendar->sec & 0x0F) + '0';
	str[8] = '\0';
	HalDisplayStr(4, 1, str); //��ʾ��Һ���ĵڶ���
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
	//���������ʾ���������ʾ RAM �ĵ�ַ
	if (y == 0)
	{
		addr = 0x00 + x; //��һ���ַ���ַ�� 0x00 ��ʼ
	}
	else
	{
		addr = 0x40 + x; //�ڶ����ַ���ַ�� 0x40 ��ʼ
	}
	//����ʼ��ʾ RAM ��ַ����д���ַ���
	DrvLcdWriteCmd(addr | 0x80); //д����ʼ��ַ
	while (*str != '\0') //����д���ַ������ݣ�ֱ����⵽������
	{
		DrvLcdWriteDat(*str);
		str++;
	}
}

