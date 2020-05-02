/*
 * Com_Types.h
 *
 *  Created on: Apr 29, 2020
 *      Author: Rita
 */

#ifndef COM_TYPES_H_
#define COM_TYPES_H_

#include "ComStack_Types.h"
#include "Com_Cfg.h"

typedef enum Com_StatusType {
	COM_INIT,
	COM_UNINIT
}Com_StatusType;

typedef uint16 Com_SignalIdType;

typedef enum ComIPduDirection {
	RECEIVE,
	SEND
} ComIPduDirection;

typedef enum ComIPduSignalProcessing {
	DEFERRED,		// signal indication / confirmations are defer-red for example to a cyclic task
	IMMEDIATE		// signal indications / confirmations are performed in Com_RxIndication/ Com_TxConfirmation
} ComIPduSignalProcessing;

typedef enum ComIPduType {
	NORMAL,			// sent or received via normal L-PDU
	TP				// sent or received via TP
} ComIPduType;

typedef struct {
	Com_SignalIdType ComHandleId;
} ComSignal;

typedef struct {
	ComIPduDirection comIPduDirection;
	uint16 ComIPduHandleId;
	ComIPduSignalProcessing comIPduSignalProcessing;
	ComIPduType comIPduType;
	PduInfoType *ComPduIdRef;
	ComSignal *comIPduSignalRef;
} ComIPdu;

typedef struct {
	uint8 ComMaxIPduCnt;
	ComIPdu *comIPdu;
}ComConfig;

typedef struct {
	ComConfig *comConfig;
}Com_ConfigType;

/* STRUCT FOR MAPPING IDS FROM COM AND PDUR */
typedef struct {
	uint16 COM_PDU_ID;
} PDU_COM_MAP;

#endif /* COM_TYPES_H_ */
