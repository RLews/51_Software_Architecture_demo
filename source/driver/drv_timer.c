

#include "drv_timer.h"






void DrvSysTimerInit(void)
{
	TMOD &= 0xF0; //���� T0 �Ŀ���λ
	TMOD |= 0x01; //���� T0 Ϊģʽ 1
	DrvReloadSysTimerCnt();
	DrvEnableSysTimerInt();
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
	TH0 = D_SYSTEM_TIMER_TH_PADDING; //���� T0 ����ֵ
	TL0 = D_SYSTEM_TIMER_TL_PADDING;
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


