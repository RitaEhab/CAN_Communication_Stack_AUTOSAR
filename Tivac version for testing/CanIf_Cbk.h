#ifndef CANIF_CBK_H_INCLUDED
#define CANIF_CBK_H_INCLUDED

void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr);

#endif // CANIF_CBK_H_INCLUDED
