/*
 * PduR.c
 *
 *  Created on: Apr 17, 2020
 *      Author: Rita
 */


#include "PduR.h"
#include "Det.h"

STATIC PduR_PBConfigType* PduR_PBConfigTypePtr = NULL_PTR;
STATIC PduR_StateType PDUR_STATE = PDUR_UNINIT;


							/* MODULE INITIALIZATION */

void PduR_Init( const PduR_PBConfigType* ConfigPtr )
{
	#if (PDUR_DEV_ERROR_DETECT == STD_ON)
		if (NULL_PTR == ConfigPtr)
		{
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_INIT_SID, PDUR_E_PARAM_POINTER);
			return;
		}
	#endif
	/* Copy init config */
	PduR_PBConfigTypePtr = ConfigPtr;
	PDUR_STATE = PDUR_ONLINE;
}


							/* LOWER LAYER COMMUNICATION SERVICES */

void PduR_CanIfRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr )
{
	#if (PDUR_DEV_ERROR_DETECT == STD_ON)
	if(PDUR_STATE != PDUR_ONLINE)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_CANIFRXINDICATION_SID, PDUR_E_UNINIT);
		return;
	}
	if(PduInfoPtr == NULL_PTR)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_CANIFRXINDICATION_SID, PDUR_E_PARAM_POINTER);
		return;
	}
	if(RxPduId != PduR_PBConfigTypePtr->pduRRoutingPaths[1]->PduRSrcPduRRef->PduRSourcePduHandleId)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_CANIFRXINDICATION_SID, PDUR_E_PDU_ID_INVALID);
		return;
	}
	#endif

	PduIdType RxId = PDU_PDUR_COM[RxPduId];
	Com_RxIndication(RxId, PduInfoPtr);
}

void PduR_CanIfTxConfirmation( PduIdType TxPduId, Std_ReturnType result )
{
	#if (PDUR_DEV_ERROR_DETECT == STD_ON)
	if(PDUR_STATE != PDUR_ONLINE)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_CANIFTXCONFIRMATION_SID, PDUR_E_UNINIT);
		return;
	}
	if(TxPduId != PduR_PBConfigTypePtr->pduRRoutingPaths[0]->PduRSrcPduRRef->PduRSourcePduHandleId)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_CANIFTXCONFIRMATION_SID, PDUR_E_PDU_ID_INVALID);
		return;
	}
	#endif

	PduIdType TxId = PDU_PDUR_COM[TxPduId];
	Com_TxConfirmation(TxId, result);
}


							/* UPPER LAYER COMMUNICATION SERVICES */

Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr )
{
	#if (PDUR_DEV_ERROR_DETECT == STD_ON)
	if(PDUR_STATE != PDUR_ONLINE)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_COMTRANSMIT_SID, PDUR_E_UNINIT);
		return E_NOT_OK;
	}
	if(PduInfoPtr == NULL_PTR)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_COMTRANSMIT_SID, PDUR_E_PARAM_POINTER);
		return E_NOT_OK ;
	}
	if(TxPduId != PduR_PBConfigTypePtr->pduRRoutingPaths[0]->PduRSrcPduRRef->PduRSourcePduHandleId)
	{
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PDUR_COMTRANSMIT_SID, PDUR_E_PDU_ID_INVALID);
		return E_NOT_OK;
	}
	#endif

	PduIdType TxId;
	uint8 i;
	for (i=0; i<PDUR_MAX_NUM_PDUS; i++)
	{
		if(PDU_CANIF_PDUR[i]->PDUR_PDU_ID == TxPduId)
		{
			TxId = i;
			break;
		}
	}

	return CanIf_Transmit(TxId, PduInfoPtr);
}
