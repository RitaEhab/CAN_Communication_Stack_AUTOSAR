#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

#include "Std_Types.h"

typedef uint32_t PduIdType;
typedef uint16_t PduLengthType;

typedef struct {
  //SDU Payload
	uint8_t *SduDataPtr;
  //SDU Length
	PduLengthType SduLength;
}PduInfoType;

typedef enum {
	BUFREQ_OK=0,
	BUFREQ_NOT_OK,
	BUFREQ_BUSY,
	BUFREQ_OVFL
}BufReq_ReturnType;

typedef enum {
	TP_DATACONF,
	TP_DATARETRY,
	TP_CONFPENDING,
	TP_NORETRY,
}TpDataStateType;

typedef struct {
	TpDataStateType TpDataState;
	PduLengthType   TxTpDataCnt;
}RetryInfoType;

typedef enum {
    TP_STMIN=0,
    TP_BS,
    TP_BC
}TPParameterType;

#endif