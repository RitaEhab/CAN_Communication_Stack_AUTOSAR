#ifndef COM_TYPES_H_INCLUDED
#define COM_TYPES_H_INCLUDED

#include "ComStack_Types.h"
#include "Com_Cfg.h"

typedef enum Com_StatusType {
	COM_INIT,
	COM_UNINIT
}Com_StatusType;

typedef uint16 Com_SignalIdType;

typedef enum ComIPduDirection {
	COM_RECEIVE,
	COM_SEND
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

#endif // COM_TYPES_H_INCLUDED
