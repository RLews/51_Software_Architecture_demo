

#include "drv_timer.h"






void Drv_SysTimerInit(void)
{
	TMOD &= 0xF0; //清零 T0 的控制位
	TMOD |= 0x01; //配置 T0 为模式 1
	D_DRV_RELOAD_SYSTIME_CNT();
	D_DRV_ENABLE_SYSTIME_INT();
	D_DRV_ENABLE_SYSTIME(); //启动 T0	
}




