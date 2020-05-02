#ifndef CANIF_H_INCLUDED
#define CANIF_H_INCLUDED


#include "CanIf_Cfg.h"
#include "Can_GeneralTypes.h"
#include "PduR_CanIf.h"

// CANIF interface for PDUR
extern const CanIf_ConfigType* canIf_ConfigPtr;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr); ///tested
void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);
Std_ReturnType CanIf_INF_GetPduHandleId(Pdu_Type* Pdu, PduIdType* PduHandleIdPtr);
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr);

#endif