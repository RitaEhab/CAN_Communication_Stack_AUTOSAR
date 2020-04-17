/*
 * Can_GeneralTypes.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CAN_GENERALTYPES_H_
#define CAN_GENERALTYPES_H_

#include "Std_Types.h"


typedef enum Can_ReturnType{
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

/* States of a CAN DRIVER */
typedef enum Can_StateType{
	CAN_READY,
	CAN_UNINIT
} Can_StateType;

/* Error states of a CAN controller */
typedef enum Can_ErrorStateType{
	CAN_ERRORSTATE_ACTIVE,
	CAN_ERRORSTATE_PASSIVE,
	CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;

/* States of a CAN controller */
typedef enum Can_ControllerStateType {
	CAN_CS_UNINIT = 0x00,
	CAN_CS_STARTED = 0x01,
	CAN_CS_STOPPED = 0x02,
	CAN_CS_SLEEP = 0x03
} Can_ControllerStateType;

/* Specifies the type (Full-CAN or Basic-CAN) of a hardware object */
typedef enum CanHandleType{
	BASIC,
	FULL
} CanHandleType;

/* Specifies the type of CAN ID */
typedef enum CanIdType{
	EXTENDED,
	MIXED,
	STANDARD
} CanIdType;

typedef enum CanObjectType{
	RECEIVE,
	TRANSMIT
} CanObjectType;

/*  Represents the Identifier of an L-PDU.
	The two most significant bits specify the frame type:
	00 CAN message with Standard CAN ID */
typedef uint32 Can_IdType;

/* Represents the hardware object handles of a CAN hardware unit */
typedef uint16 Can_HwHandleType;

/* MOVED FROM COMSTACK_TYPES.H*/
/* Maximum number of PDUs (Protocol data unit) used within one software module */
typedef uint8 PduIdType;

/* This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and CanId (id) for any CAN L-SDU. */
typedef struct{
	PduIdType swPduHandle;			// Pdu unique number in this software module ?
	uint8 length;
	Can_IdType id;					// ADDED TAKE CARE !!
	uint8* sdu;
} Can_PduType;

/*  This type defines a data structure which clearly provides an Hardware Object Handle
	including its corresponding CAN Controller and therefore CanDrv as well as the specific CanId. */
typedef struct{
	Can_IdType CanId;
	Can_HwHandleType Hoh;
	uint8 ControllerId;
} Can_HwType;

typedef struct{
	uint16 CanControllerBaudRate;				// baudrate of the controller in kbps
	uint16 CanControllerBaudRateConfigID;		// Uniquely identifies a specific baud rate configuration
	uint8 CanControllerPropSeg;					// propagation delay in time quantas
	uint8 CanControllerSeg1;					// phase segment 1 in time quantas
	uint8 CanControllerSeg2;					// phase segment 2 in time quantas
	uint8 CanControllerSyncJumpWidth;			// synchronization jump width for the controller in time quantas
} CanControllerBaudrateConfig;

typedef struct {
	uint8 CanControllerId;
	CanControllerBaudrateConfig *canControllerBaudrateConfig;
} CanController;

typedef struct {
	uint8 CanHwFilterCode;				// specifies (with the filter mask) the IDs range that passes the hardware filter
	uint16 CanHwFilterMask;				// Bits holding a 0 mean don't care, i.e. do not compare the message's identifier in the respective bit position
} CanHwFilter;

typedef struct {
	CanHandleType canHandleType;
	uint16 CanHwObjectCount;
	CanIdType canIdType;			// OR USE CAN_IDTYPE WHICH INDICATES FULL IDENTIFIER NOT ONLY THE TYPE ?
	uint8 CanObjectId;					// Holds the handle ID of HRH or HTH
	CanObjectType canObjectType;
	CanController *CanControllerRef;
	CanHwFilter *canHwFilter;
} CanHardwareObject;

typedef struct {
	CanController *canController;
	CanHardwareObject *canHardwareObject[];
} Can_ConfigType;

#endif /* CAN_GENERALTYPES_H_ */
