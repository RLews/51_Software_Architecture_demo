

#include "hal_paltform.h"

bool_t SysEnterCritical(void)
{
	bool_t sta = EA;
	EA = 0;

	return sta;
}

void SysExitCritical(bool_t sta)
{
	EA = sta;
}

