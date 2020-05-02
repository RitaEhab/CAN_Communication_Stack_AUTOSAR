#ifndef CANIF_CBK_H
#define CANIF_CBK_H

/// CANIF Interface for CAN Driver 


#include "PduR_PbCfg.h"
#include "Can_GeneralTypes.h" 

void CanIf_TxConfirmation(PduIdType CanTxPduId); ///tested

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr); ///tested

// Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType * PduInfoPtr); ///tested
// void CanIf_ControllerBusOff(uint8 ControllerId); ///tested
// void CanIf_ConfirmPnAvailability(uint8 TransceiverId); ///tested
// void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId); ///tested
// void CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId); ///tested
// void CanIf_CurrentIcomConfiguration(uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error); ///tested


#endif // CANIF_CBK_H