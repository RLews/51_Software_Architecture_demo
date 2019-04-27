

#include "drv_timer.h"

static void DrvSysTimerInit(void);
static void DrvEnableSysTimerInt(void);
static void DrvDisableSysTimerInt(void);
static void DrvReloadSysTimerCnt(void);
static uint8_t DrvGetSysTimerIntFlag(void);
static uint16_t DrvGetSysTimerCnt(void);



D_SOFTWARE_INTERFACE drvTimerInterface_t drvTimerInterface = {
	DrvSysTimerInit,
	DrvEnableSysTimerInt,
	DrvDisableSysTimerInt,
	DrvReloadSysTimerCnt,
	DrvGetSysTimerCnt,
	DrvGetSysTimerIntFlag
};



static void DrvSysTimerInit(void)
{
	TMOD &= 0xF0; //清零 T0 的控制位
	TMOD |= 0x01; //配置 T0 为模式 1
	DrvReloadSysTimerCnt();
	DrvEnableSysTimerInt();
	TR0 = 1; //启动 T0	
}

static void DrvEnableSysTimerInt(void)
{
	ET0 = 1; //使能 T0 中断
	TR0 = 1; //启动 T0	
}

static void DrvDisableSysTimerInt(void)
{
	ET0 = 0; 
	TR0 = 0;
}

static void DrvReloadSysTimerCnt(void)
{
#ifdef D_USE_ONEMS_INTRRUPET_MODE
	TH0 = 0xFC; //加载 T0 重载值
	TL0 = 0x18;
#else
	TH0 = 0; //加载 T0 重载值
	TL0 = 0;
#endif
}

static uint8_t DrvGetSysTimerIntFlag(void)
{
	return TF0;
}

static uint16_t DrvGetSysTimerCnt(void)
{
	uint16_t cnt = 0;

	DrvDisableSysTimerInt();
	
	cnt = TH0;
	cnt = (cnt << 8) + TL0;

	DrvEnableSysTimerInt();

	return cnt;
}


