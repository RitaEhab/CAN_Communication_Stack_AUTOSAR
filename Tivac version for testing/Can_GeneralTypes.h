#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H


#include <stdint.h>
typedef uint32_t PduIdType;

typedef uint32_t Can_IdType; /* Assuming extended IDs are used, revert to uint16 for standard IDs, 0x Std ID, 1x Ext ID*/
/* Use uint16 if more than 255 H/W handles otherwise, uint8*/

 /* @req CAN429 */
typedef uint16_t Can_HwHandleType;

typedef enum Can_StateTransitionType {
	CAN_T_STOP, /* Cannot request mode CAN_UNINIT */
	CAN_T_START,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

/** @req 4.0.3/CAN039 */
typedef enum Can_ReturnType {
	CAN_OK, /* Successful operation */
	CAN_NOT_OK, /* Error occurred or wakeup event occurred during sleep transition */
	CAN_BUSY /* Transmit request not processed because no transmit object was available*/
} Can_ReturnType;

typedef enum Can_ProcessingType {
	INTERRUPT,
	POLLING
} Can_ProcessingType;

typedef enum CanHandleType {
	BASIC,
	FULL
} CanHandleType;

typedef struct {
	uint16_t canObjectId;
	CanHandleType canHandleType;
} CanHardwareObject;

typedef struct Can_ControllerType {
	/* @req CAN315 */
	char CanControllerActivation; ////changed it

	/* @req CAN382 */
	uint32_t CanControllerBaseAddress;

	/* @req CAN316 */
	uint8_t CanControllerId;

	/* @req CAN314 */
	Can_ProcessingType CanBusOffProcessing;

	/* @req CAN317 */
	Can_ProcessingType CanRxProcessing;

	/* @req CAN318 */
	Can_ProcessingType CanTxProcessing;
} Can_ControllerType;

typedef struct Can_HardwareObjectType {
	CanHandleType CanHandleType;
} Can_HardwareObjectType;

typedef struct Can_ConfigSetType {
	Can_ControllerType CanController;
	Can_HardwareObjectType CanHardwareObject;
} Can_ConfigSetType;

typedef struct Can_HwType {
	Can_IdType CanId; /* Standard/Extended CAN ID of CAN LPDU */
	Can_HwHandleType Hoh; /* ID of the corresponding HardwareObject Range */
	uint8_t ControllerId; /* ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;

/** @req 4.0.3/CAN415 */
typedef struct Can_PduType_s {
	// private data for CanIf,just save and use for callback
	PduIdType   swPduHandle;
	// the CAN ID, 29 or 11-bit
	Can_IdType 	id;
	// Length, max 8 bytes
	uint8_t		length;
	// data ptr
	uint8_t 		*sdu;
} Can_PduType;

typedef struct Can_MainFunctionRWPeriodType {
	float CanMainFunctionPeriod;
} Can_MainFunctionRWPeriodType;

typedef struct Can_Type {
	Can_ConfigSetType CanConfigSet;
} Can_Type;

typedef enum Can_TrcvModeType {
	CANTRCV_TRCVMODE_NORMAL = 0, /* Transceiver mode NORMAL */
	CANTRCV_TRCVMODE_STANDBY, /* Transceiver mode STANDBY */
	CANTRCV_TRCVMODE_SLEEP /* Transceiver mode SLEEP */
} Can_TrcvModeType;

typedef enum Can_TrcvWakeupReasonType {
	CANTRCV_WU_ERROR = 0, /* This value may only be reported when error was reported to DEM before. Wake-up reason was not detected */
	CANTRCV_WU_NOT_SUPPORTED, /* The transceiver does not support any information for the wakeup reason. */
	CANTRCV_WU_BY_BUS, /* Network has caused the wake up of the ECU */
	CANTRCV_WU_BY_PIN, /* Wake-up event at one of the transceiver's pins (not at the CAN bus). */
	CANTRCV_WU_INTERNALLY, /* Network has woken the ECU via a request to NORMAL mode */
	CANTRCV_WU_RESET, /* Wake-up is due to an ECU reset */
	CANTRCV_WU_POWER_ON /* Wake-up is due to an ECU reset after power on. */
} Can_TrcvWakeupReasonType;

typedef enum Can_TrcvWakeupModeType {
	CANTRCV_WUMODE_ENABLE = 0, /* Wakeup events notifications are enabled on the addressed network. */
	CANTRCV_WUMODE_DISABLE, /* Wakeup events notifications are disabled on the addressed network. */
	CANTRCV_WUMODE_CLEAR /* A stored wakeup event is cleared on the addressed network */
} Can_TrcvWakeupModeType;



#endif /* CAN_GENERAL_TYPES_H */