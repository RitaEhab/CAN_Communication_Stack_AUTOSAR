#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Std_Types.h"

typedef struct {
	uint32 ui32GpioPeripheral;
	uint32 ui32RxPinConfig;
	uint32 ui32TxPinConfig;
	uint32 ui32Port;
	uint8  ui8Pins;
	uint32 ui32CanPeripheral;
	uint32 ui32CanBase;
	uint32 ui32BitRate;
	uint32 pin_id;
	uint32 controller_id;
	uint32 receive_object;
} Can_ControllerConfigType;

typedef struct {
	Can_ControllerConfigType **canx_config;
} Can_ConfigType;

#endif