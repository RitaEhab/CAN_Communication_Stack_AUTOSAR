/** incomplete Com code file used as a test to PDUR module */

#include "Com.h"

#include "C:\Keil\Labware\utils\uartstdio.h"

Std_ReturnType ComSendSignal(uint32_t Id, uint8_t Msg[], uint8_t length) {
	/*printf("COM Received PDU from RTE\n");
	printf("ID: %d\n" , Id);
	printf("MSG: %s\n" , Msg);
	printf("----------------------------------\n");*/
	
	UARTprintf("Com got a message; Id: %d, Length: %d, Data: ", 
							Id, length);
	for(int i=0; i<length; i++) {
		UARTprintf("%02X ", Msg[i]);
	}
	UARTprintf("\n");
	
	/** formulating I-PDU */
	const PduInfoType distanceMsg = {
		.SduDataPtr = Msg,
		.SduLength = length
	};
	
	PduIdType PduHandleId;

	//TODO: simplify and use only one PDU Handle
	if (PduR_INF_GetSourcePduHandleId(&Pdus[Id], &PduHandleId) == E_OK) {
		/*printf("COM Sending to PDUR\n");
		printf("ID: %d\n", Id);
		printf("MSG: %s\n", Msg);
		printf("----------------------------------\n");*/
		return PduR_ComTransmit(PduHandleId, &distanceMsg);
		//PduR_ComCancelTransmit(PduHandleId);
	}
	else {
		return E_NOT_OK;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr) {
	/**
	the upper layer module (called module) shall check whether the
	available data fits into the buffer size reported by PduInfoPtr->SduLength.
	If it fits, it shall copy its data into the buffer provided by PduInfoPtr ->SduDataPtr
	and update the length of the actual copied data in PduInfoPtr->SduLength.
	If not, it returns E_NOT_OK without changing PduInfoPtr.
	*/
	printf("\nnow in Com Trigger Transmit\n");
	Std_ReturnType retVal = E_OK;
	uint8_t distMsg[] = "1234Msg";  //Message to be transmitted
	if (sizeof(distMsg) / sizeof(distMsg[0]) < PduInfoPtr->SduLength)
	{
		if (!memcpy((void *)PduInfoPtr->SduDataPtr,
			(void *)distMsg,
			sizeof(distMsg) / sizeof(distMsg[0]))
			) {
			retVal = E_NOT_OK;
		}
		else {
			PduInfoPtr->SduLength = sizeof(distMsg) / sizeof(distMsg[0]);
		}
	}
	else {
		retVal = E_NOT_OK;
	}
	return retVal;
}

void Com_RxIndication(PduIdType PduHandleId, const PduInfoType* PduInfoPtr) {
	/*printf("COM Received PDU from PDUR\n");
	printf("ID: %d\n", PduHandleId);
	printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
	printf("----------------------------------\n");*/
	UARTprintf("Message arrived to Com, CanId: %d, Length: %d, Data: ", 
			PduHandleId, PduInfoPtr->SduLength);
	for(int i=0; i<PduInfoPtr->SduLength; i++) {
		UARTprintf("%02X ", PduInfoPtr->SduDataPtr[i]);
	}
	UARTprintf("\n");
}

void Com_TxConfirmation(PduIdType PduHandleId, Std_ReturnType result) {
	printf("\nnow in Com TX confirmation\n");
	printf("Can -> Com confirmation has finished\n");
}

BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,
	PduLengthType TpSduLength, PduLengthType* bufferSizePtr) {

	printf("now in Com start of reception\n");
	return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info,
	PduLengthType* bufferSizePtr) {

	printf("now in Com copy RX data\n");
	return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info,
	RetryInfoType* retry, PduLengthType* availableDataPtr) {

	printf("now in Com copy TX data\n");
	return BUFREQ_OK;
}

/**
	Description  : query global I-PDU reference in Com configuration .
	inputs       : Pdu            | Reference to global PDU .
	output       : DestPduId      | Identifier to local I-PDU .
	I/O          : None
	return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
Std_ReturnType Com_INF_GetPduHandleId(Pdu_Type *Pdu, PduIdType *PduHandleIdPtr) {
	Std_ReturnType Std_Ret = E_NOT_OK;

	for (uint8_t i = 0; i < ComConfiguration.ComMaxIPduCnt; i++) {
		if (ComConfiguration.ComIPdu[i].PduIdRef == Pdu) {
			Std_Ret = E_OK;
			*PduHandleIdPtr = ComConfiguration.ComIPdu[i].IPduHandleId;
		}
	}
	return Std_Ret;
}