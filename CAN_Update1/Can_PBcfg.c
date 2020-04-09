/*
 * Can_PBcfg.c
 *
 *  Created on: Feb 8, 2020
 *      Author: Rita
 */

#include "Can_Cfg.h"
#include "Can.h"
/*
const Can_ConfigType Can_Configuration =
{
		init_module_disable, init_freeze_enable, init_RX_FIFO_enable, init_halt,
		init_soft_reset, init_supervisor_mode, init_warning_interrupt_enable,
		init_self_reception_disable, init_IRMQ, init_DMA_enable, init_pretended_network_enable,
		init_local_priority_enable, init_abort_enable, init_FD_operation_enable,
		init_IDAM, init_MAXMB
};
*/
const CanControllerBaudrateConfig canControllerBaudrateConfig =
{
		.CanControllerBaudRate = 500,			// Clock rate = 16MHz
		.CanControllerBaudRateConfigID = 0,
		.CanControllerPropSeg = 4,				// 0b100
		.CanControllerSeg1 = 7,					// 0b111
		.CanControllerSeg2 = 1,					// 0b001
		.CanControllerSyncJumpWidth = 3			// 0b11
};

/*		PREVIOUS YEAR
 * PRESDIV = 4
 * RJW = 3
 * PSEG1 = 3
 * PSEG2 = 3
 * PROPSEG = 6
 * SMP = 1			 3 samples to determine bit value at Rx input
 * */

/*		OURS
 * PRESDIV = 0
 * RJW = 3
 * PSEG1 = 7
 * PSEG2 = 1
 * PROPSEG = 4
 * SMP = 1			 3 samples to determine bit value at Rx input
 * */
const CanController canController =
{
		.CanControllerId = 0,
		.canControllerBaudrateConfig = &canControllerBaudrateConfig
};

const CanHwFilter canHwFilter =
{
		.CanHwFilterCode = 1,				// TO BE CHANGED
		.CanHwFilterMask = 0x0001			// TO BE CHANGED
};

/* Hardware Receive Handle */
const CanHardwareObject canHardwareReceiveObject =
{
		.canHandleType = FULL,
		.CanHwObjectCount = 2,
		.canIdType = STANDARD,
		.CanObjectId = 0,			// HRH = 0
		.canObjectType = RECEIVE,
		.CanControllerRef = &canController,
		.canHwFilter = &canHwFilter
};

/* Hardware Transmit Handle */
const CanHardwareObject canHardwareTransmitObject =
{
		.canHandleType = FULL,
		.CanHwObjectCount = 2,
		.canIdType = STANDARD,
		.CanObjectId = 1,			// HTH = 1
		.canObjectType = TRANSMIT,
		.CanControllerRef = &canController,
		.canHwFilter = &canHwFilter
};

const Can_ConfigType canConfigSet =
{
		.canController = &canController,
		.canHardwareObject[0] = &canHardwareReceiveObject,
		.canHardwareObject[1] = &canHardwareTransmitObject
};
