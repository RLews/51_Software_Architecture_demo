

#include "drv_timer.h"






void DrvSysTimerInit(void)
{
	TMOD &= 0xF0; //���� T0 �Ŀ���λ
	TMOD |= 0x01; //���� T0 Ϊģʽ 1
	D_DRV_RELOAD_SYSTIME_CNT();
	D_DRV_ENABLE_SYSTIME_INT();
	D_DRV_ENABLE_SYSTIME(); //���� T0	
}




