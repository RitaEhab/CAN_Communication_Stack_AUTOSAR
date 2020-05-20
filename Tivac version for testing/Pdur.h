#ifndef PDUR_H_
#define PDUR_H_

#include "Std_Types.h"
#include "PduR_Cfg.h"
#include "PduR_PbCfg.h"
#include "PduR_Types.h"
#include <stdio.h>

extern const PduR_PBConfigType* PduRConfig;
extern PduR_StateType PduRState;
extern Pdu_Type Pdus[];

void PduR_Init(const PduR_PBConfigType* ConfigPtr);
//PduR_PBConfigIdType PduR_GetConfigurationId(void);
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);
//void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

Std_ReturnType PduR_INF_GetSourcePduHandleId(Pdu_Type *Pdu, PduIdType *PduHandleIdPtr);
Std_ReturnType PduR_INF_RouteTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);
void PduR_INF_TxConfirmation(PduIdType PduId, Std_ReturnType result);
void PduR_INF_RouteTxConfirmation(PduIdType pduId, Std_ReturnType result);
void PduR_INF_RxIndication(PduIdType pduId, const PduInfoType* pduInfoPtr);
void PduR_INF_RouteRxIndication(const PduRDestPdu_type *destination, const PduInfoType *PduInfo);

#endif