

#include "drv_timer.h"






void DrvSysTimerInit(void)
{
	TMOD &= 0xF0; //���� T0 �Ŀ���λ
	TMOD |= 0x01; //���� T0 Ϊģʽ 1
	DrvReloadSysTimerCnt();
#ifdef D_USE_ONEMS_INTRRUPET_MODE
	DrvEnableSysTimerInt();
#endif
	TR0 = 1; //���� T0	
}

void DrvEnableSysTimerInt(void)
{
	ET0 = 1; //ʹ�� T0 �ж�
	TR0 = 1; //���� T0	
}

void DrvDisableSysTimerInt(void)
{
	ET0 = 0; 
	TR0 = 0;
}

void DrvReloadSysTimerCnt(void)
{
#ifdef D_USE_ONEMS_INTRRUPET_MODE
	TH0 = 0xFC; //���� T0 ����ֵ
	TL0 = 0x18;
#else
	TH0 = 0; //���� T0 ����ֵ
	TL0 = 0;
#endif
}

uint8_t DrvGetSysTimerIntFlag(void)
{
	return TF0;
}

uint16_t DrvGetSysTimerCnt(void)
{
	uint16_t cnt = 0;

	DrvDisableSysTimerInt();
	
	cnt = TH0;
	cnt = (cnt << 8) + TL0;

	DrvEnableSysTimerInt();

	return cnt;
}


