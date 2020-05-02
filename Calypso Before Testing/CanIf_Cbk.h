/*
 * CanIf_Cbk.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr);

#endif /* CANIF_CBK_H_ */
