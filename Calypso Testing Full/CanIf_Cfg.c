#include "CanIf.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "PduR_Cfg.h"

								/* SOME CONTAINERS FROM CAN DRV */


const CanController can_Controller =
{
		.CanControllerId = 0
};

/* Hardware Receive Handle */
const CanHardwareObject can_HardwareReceiveObject =
{
		.canHandleType = FULL,
		.CanHwObjectCount = 2,
		.canIdType = STANDARD,
		.CanObjectId = 0,			// HRH = 0
		.canObjectType = RECEIVE,
		.CanControllerRef = &can_Controller
};

/* Hardware Transmit Handle */
const CanHardwareObject can_HardwareTransmitObject =
{
		.canHandleType = FULL,
		.CanHwObjectCount = 2,
		.canIdType = STANDARD,
		.CanObjectId = 1,			// HTH = 1
		.canObjectType = TRANSMIT,
		.CanControllerRef = &can_Controller
};

const Can_HwType can_ReceiveMailbox = {
		.CanId = 0x7,
		.Hoh = 0,				// HRH = 0
		.ControllerId = 0
};


                                /* CANIF CONTAINERS */

							/* CanIfCtrlCfg CONTAINER */

CanIfCtrlCfg canIfCtrlCfg = {
	.CanIfCtrlId = 0,
	.CanIfCtrlWakeupSupport = FALSE,
	.CanIfCtrlCanCtrlRef = &can_Controller
};

CanIfHthCfg canIfHthCfg = {
	.CanIfHthCanCtrlIdRef = &canIfCtrlCfg,
	.CanIfHthIdSymRef = &can_HardwareTransmitObject
};

CanIfHrhCfg canIfHrhCfg = {
	.CanIfHrhSoftwareFilter = FALSE,
	.CanIfHrhCanCtrlIdRef = &canIfCtrlCfg,
	.CanIfHrhIdSymRef = &can_HardwareReceiveObject
};

CanIfInitHohCfg canIfInitHohCfg = {
	.canIfHrhCfg = &canIfHrhCfg,
	.canIfHthCfg = &canIfHthCfg
};

CanIfBufferCfg canIfBufferCfg = {
	.CanIfBufferSize = 1,
	.canIfBufferHthRef = &canIfHthCfg
};

PduInfoType can_PduType={
	.SduLength = 8
};

/* CONTAINER FOR TRANSMISSION */
CanIfTxPduCfg canIfTxPduCfg = {
	.CanIfTxPduCanId = 7,
	.CanIfTxPduCanIdMask = 7,
	.canIfTxPduCanIdType = STANDARD_CAN,
	.CanIfTxPduId = 3,
	.CanIfTxPduPnFilterPdu = FALSE,
	.CanIfTxPduReadNotifyStatus = FALSE,
	.CanIfTxPduTriggerTransmit = FALSE,
	.CanIfTxPduTruncation = FALSE,
	.canIfTxPduType = Static,
	.CanIfTxPduBufferRef = &canIfBufferCfg,
	.CanIfTxPduRef = &can_PduType
};

/* CONTAINER FOR RECEPTION */
CanIfRxPduCfg canIfRxPduCfg = {
	.CanIfRxPduCanId = 7,
	.CanIfRxPduCanIdMask = 7,
	.canIfRxPduCanIdType = STANDARD_CAN,
	.CanIfRxPduDataLength = 1,
	.CanIfRxPduId = 2,
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

const CanIf_ConfigType canIf_ConfigType = {
	.CanIf_InitCfg = &canIfInitCfg
};

/* PREVIOUS YEAR
 * assuming msgId = 7, hth = 0, driverId = 1, interfacId = 2
 * msgId: 11 bits, hth: 8 bits, driverId: 4 bits, interfaceId: 4 bits
 * */
