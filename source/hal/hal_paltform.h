

#ifndef __HAL_PALTFORM_H
#define __HAL_PALTFORM_H

#include "drv_paltform.h"

#define D_SYSTEM_ENTER_CRITICAL()			SysEnterCritical()/* TODO: add function */
#define D_SYSTEM_EXIT_CRITICAL(sta)			SysExitCritical(sta)/* TODO: add function */

bool_t SysEnterCritical(void);
void SysExitCritical(bool_t sta);


#endif

