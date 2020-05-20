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
	if(SignalId != Com_ConfigTypePtr->comConfig->comIPdu[1].comIPduSignalRef->ComHandleId)
	{
		Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_SendSignal_SID, COM_E_PARAM);
	}
#endif

	PduInfoType PduInfoPtr;
	PduInfoPtr.SduLength = Com_ConfigTypePtr->comConfig->comIPdu->ComPduIdRef->SduLength;
	PduInfoPtr.SduDataPtr = SignalDataPtr;

	PduIdType TxPduId = Com_ConfigTypePtr->comConfig->comIPdu[1].ComIPduHandleId;
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
	if (RxPduId != Com_ConfigTypePtr->comConfig->comIPdu[0].ComIPduHandleId)
    {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, Com_RxIndication_SID, COM_E_PARAM);
    }
	else
#endif
	{
		uint8 Data = *(PduInfoPtr->SduDataPtr);
		output (Data);
		return;
	}
}

void Com_TxConfirmation( PduIdType TxPduId, Std_ReturnType result )
{
    return;
}
