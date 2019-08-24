

#ifndef HAL_PALTFORM_H
#define HAL_PALTFORM_H

#include "drv_paltform.h"

#define D_SYSTEM_ENTER_CRITICAL()			Hal_SysEnterCritical()/* TODO: add function */
#define D_SYSTEM_EXIT_CRITICAL(sta)			Hal_SysExitCritical(sta)/* TODO: add function */

bool_t Hal_SysEnterCritical(void);
void Hal_SysExitCritical(bool_t sta);


#endif

