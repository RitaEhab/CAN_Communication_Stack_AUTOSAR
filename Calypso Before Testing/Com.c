/*
 * Com.c
 *
 *  Created on: Apr 29, 2020
 *      Author: Rita
 */
#include "PduR.h"
#include "Com.h"
#include "Det.h"
#include "Logic.h"

STATIC Com_ConfigType *Com_ConfigTypePtr = NULL_PTR;
STATIC Com_StatusType COM_STATE = COM_UNINIT;


							/* MODULE INITIALIZATION */

void Com_Init( const Com_ConfigType* config )
{
	#if COM_DEV_ERROR_DETECT == STD_ON
		if (config == NULL_PTR)
		{
			Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INIT_SID, COM_E_PARAM_POINTER);
		}
	#endif

	Com_ConfigTypePtr=config;
	COM_STATE=COM_INIT;
}


							/* COMMUINCATION SERVICES */

uint8 Com_SendSignal( Com_SignalIdType SignalId, const void* SignalDataPtr )
{
	// SignalId is different from PDU ID


#if COM_DEV_ERROR_DETECT == STD_ON
	if (COM_STATE == COM_UNINIT)
	{
		Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_SendSignal_SID, COM_E_UNINIT);
	}
	if(SignalId != Com_ConfigTypePtr->comConfig->comIPdu->ComIPduSignalRef->ComHandleId)
	{
		Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_SendSignal_SID, COM_E_PARAM);
	}
#endif

	const PduInfoType PduInfoPtr;
	PduInfoPtr->SduLength = Com_ConfigTypePtr->comConfig->comIPdu->ComPduIdRef->SduLength;
	PduInfoPtr->SduDataPtr = SignalDataPtr;

	uint16 ComIPduId = Com_ConfigTypePtr->comConfig->comIPdu->ComIPduHandleId;
	PduIdType TxPduId;
	uint8 i;
	for (i=0; i<Com_ConfigTypePtr->comConfig->ComMaxIPduCnt; i++)
	{
		if(PDU_PDUR_COM[i]->COM_PDU_ID == ComIPduId)
		{
			TxPduId = i;
			break;
		}
	}
	if (PduR_ComTransmit(TxPduId, &PduInfoPtr) == E_OK)
	{
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}


					/* CALLBACK FUNCTIONS AND NOTIFICATIONS */

void Com_RxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr )
{
#if COM_DEV_ERROR_DETECT == STD_ON
	if (COM_STATE == COM_UNINIT)
	{
		Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_RxIndication_SID, COM_E_UNINIT);
	}
	if(PduInfoPtr == NULL_PTR)
	{
		Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_RxIndication_SID, COM_E_PARAM_POINTER);
	}
	else
#endif
	{
		uint8 Data = *(PduInfoPtr->SduDataPtr);
		output (Data);
		return;
	}
}
