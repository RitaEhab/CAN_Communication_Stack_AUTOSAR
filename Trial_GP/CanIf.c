/*
 * CanIf.c
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "Dem.h"
#include "Det.h"
#include "MemMap.h"

/* TO BE ADDED */
// #include "PduR_CanIf.h"
// #include "PduR_Cbk.h"

CanIf_StateType CANIF_STATE = CANIF_UNINIT;

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
	/* Check, initialization status of CanIf */
	if (CANIF_STATE != CANIF_READY)
	{
		return E_NOT_OK;
	}
	else
	{
		/* Determine HTH for access to the CAN hardware transmit object */
		Can_HwHandleType HTH = 3;	// Ay habd l3'ayet manshouf ngibo mnein
		Can_PduType Pdu;
		Pdu->swPduHandle = TxPduId;
		//Pdu->
		Can_Write(HTH,Pdu);
		return E_OK;
	}
}
