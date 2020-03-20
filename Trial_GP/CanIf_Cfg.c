/*
 * CanIf_Cfg.c
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#include "CanIf.h"
#include "Can.h"
#include "Can_Cfg.h"

//#include "PduR_Cfg.h"

								/* CanIfCtrlCfg CONTAINER */

CanIfCtrlCfg canIfCtrlCfg = {
	CanIfCtrlId = 0,
	CanIfCtrlWakeupSupport = FALSE,

	/* NOT NEEDED AS WE ARE USING ONLY ONE CONTROLLER */
	//CanIfCtrlCanCtrlRef = NULL_PTR,
};



