

#include "hal_paltform.h"

bool_t Hal_SysEnterCritical(void)
{
	bool_t sta = EA;
	EA = 0;

	return sta;
}

void Hal_SysExitCritical(bool_t sta)
{
	EA = sta;
}

