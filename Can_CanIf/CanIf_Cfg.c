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
	.CanIfCtrlId = canController->CanControllerId,
	.CanIfCtrlWakeupSupport = FALSE,

	/* NOT NEEDED AS WE ARE USING ONLY ONE CONTROLLER */
	.CanIfCtrlCanCtrlRef = &canController
};

CanIfHthCfg canIfHthCfg = {
	.CanIfHthCanCtrlIdRef = &canIfCtrlCfg,
	.CanIfHthIdSymRef = &canHardwareTransmitObject
};

CanIfHrhCfg canIfHrhCfg = {
	.CanIfHrhSoftwareFilter = FALSE,
	.CanIfHrhCanCtrlIdRef = &canIfCtrlCfg,
	.CanIfHrhIdSymRef = &canHardwareReceiveObject
};

CanIfInitHohCfg canIfInitHohCfg = {
	.canIfHrhCfg = &canIfHrhCfg,
	.canIfHthCfg = &canIfHthCfg
};

CanIfBufferCfg canIfBufferCfg = {
	.CanIfBufferSize = 1,
	.canIfBufferHthRef = &CanIfHthCfg
};

/* NOT SURE AT ALL
 * OR USE PduInfoType ??
 * */
Can_PduType can_PduType = {
	.swPduHandle = 7,		// TO BE EDITED!!
	.length = 1,			// TO BE EDITED!!
	.id = 0,				// TO BE EDITED!!
	.sdu = NULL_PTR			// TO BE EDITED!!
};

/* TO BE EDITED >> IDS
 * Calypso does not need its own TxPdu
 * */
CanIfTxPduCfg canIfTxPduCfg = {
	.CanIfTxPduCanId = 7,								// CanId => 11 bits or CanDrv id ?
	.CanIfTxPduCanIdMask = 7,
	.canIfTxPduCanIdType = STANDARD_CAN,
	.CanIfTxPduId = 7,									// PDUID == CANID ?
	.CanIfTxPduPnFilterPdu = FALSE,
	.CanIfTxPduReadNotifyStatus = FALSE,
	.CanIfTxPduTriggerTransmit = FALSE,
	.CanIfTxPduTruncation = FALSE,
	.canIfTxPduType = Static,
	.CanIfTxPduBufferRef = &canIfBufferCfg
	.CanIfTxPduRef = &can_PduType
};

CanIfRxPduCfg canIfRxPduCfg = {
	.CanIfRxPduCanId = 7,								// CanId => 11 bits or CanDrv id ?
	.CanIfRxPduCanIdMask = 7,
	.canIfRxPduCanIdType = STANDARD_CAN,
	.CanIfRxPduDataLength = 1,
	.CanIfRxPduId = 7,									// PduId ?
	.CanIfRxPduReadData = FALSE,
	.CanIfRxPduReadNotifyStatus = FALSE,
	.CanIfRxPduHrhIdRef = &canIfHrhCfg,
	.CanIfRxPduRef = &can_PduType
};

CanIfInitCfg canIfInitCfg = {
	.canIfInitCfgSet = 0,
	.canIfMaxBufferSize = 1,
	.canIfMaxRxPduCfg = 1,
	.canIfMaxTxPduCfg = 1,
	.canIfBufferCfg = &canIfBufferCfg,
	.canIfInitHohCfg = &canIfInitHohCfg,
	.canIfRxPduCfg = &canIfRxPduCfg,
	.canIfTxPduCfg = &canIfTxPduCfg,
};


/* PREVIOUS YEAR
 * assuming msgId = 7, hth = 0, driverId = 1, interfacId = 2
 * msgId: 11 bits, hth: 8 bits, driverId: 4 bits, interfaceId: 4 bits
 * */
