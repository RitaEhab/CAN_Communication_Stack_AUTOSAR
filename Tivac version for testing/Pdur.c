#include "PduR_PbCfg.h"
/*
#include "Dem.h"
#include "Det.h"
*/
#if PDUR_CANIF_SUPPORT == STD_ON
#include "CanIf.h"
#endif
#if PDUR_COM_SUPPORT == STD_ON
#include "Com.h"
#endif
#include "C:\Keil\Labware\utils\uartstdio.h"
#include <inttypes.h>


//extern bool com2pdur;

/* ========================================================================== */
/*                         PDUR MODULE FUNCTIONS							                */
/* ========================================================================== */

//PDUR Initial State
PduR_StateType PduRState = PDUR_UNINIT;

//Global PDUR coniguration pointer
const PduR_PBConfigType* PduRConfig;

/*
  Description:  Initialize the PDU router
  Parameters:   ConfigPtr => Pointer to post build configuration
  Return Value: Nothing
*/
void PduR_Init(const PduR_PBConfigType* ConfigPtr) {
	if (ConfigPtr == NULL) {
		PduRState = PDUR_REDUCED;
	}
	else if (PduRState != PDUR_UNINIT) {
		PduRState = PDUR_REDUCED;
	}
	else {
		PduRState = PDUR_ONLINE;
		PduRConfig = ConfigPtr;
	}
}

/*
	Description  : query global I-PDU reference in PDUR configuration (routing paths sources)
	inputs       : Pdu            | Reference to global PDU .
	output       : PduHandleIdPtr | Identifier to local I-PDU .
	I/O          : None
	Return value : Std_ReturnType | Determine if I-PDU is exist or not .
*/
Std_ReturnType PduR_INF_GetSourcePduHandleId(Pdu_Type* Pdu, PduIdType* PduHandleIdPtr) {
	Std_ReturnType Std_Ret = E_NOT_OK;

	if (PduRConfig->RoutingPaths[0] == NULL || Pdu == NULL) {
		//detect error
		return E_NOT_OK;
	}
	uint8_t i = 0;
	for ( i = 0; PduRConfig->RoutingPaths[i] != NULL; i++) {
		if (PduRConfig->RoutingPaths[i]->PduRSrcPduRef->SrcPduRef == Pdu) {
			Std_Ret = E_OK;
			*PduHandleIdPtr = PduRConfig->RoutingPaths[i]->PduRSrcPduRef->SourcePduHandleId;
		}
	}
	return Std_Ret;
}

/* ========================================================================== */
/*                          UPPER LAYER - COM MODULE                          */
/* ========================================================================== */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_COM_SUPPORT == STD_ON)
/*
  Description:  Requests the transmission of a PDU
  Parameters:   TxPduId     => The ID of the transmitted PDU
				PduInfoPtr  => The length and data of the transmitted PDU
  Return Value: The transmission request succeded or failed
*/
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {

	/*printf("PDUR Received PDU from COM\n");
	printf("ID: %d\n", TxPduId);
	printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
	printf("----------------------------------\n");*/
	//Printing the message details to UART
	UARTprintf("PduR got a message; Id: %d, Length: %d, Data: ",
		TxPduId, PduInfoPtr->SduLength);
	for (int i = 0; i < PduInfoPtr->SduLength; i++) {
		UARTprintf("%02X ", PduInfoPtr->SduDataPtr[i]);
	}
	UARTprintf("\n");

	return PduR_INF_RouteTransmit(TxPduId, PduInfoPtr);
}
#endif

// return 1 if PduId corresponds to TX pdu 
bool Is_Pdu_Tx(PduIdType PduId) {
	uint32 i;
	for(i = 0; i<TX_PDU_CNT; i++) {
		if(PduId == Tx_Pdu_Ids[i]) {
			return 1;
		}
	}
	return 0;
}

// return 1 if PduId corresponds to RX pdu 
bool Is_Pdu_Rx(PduIdType PduId) {
	uint32 i;
	for(i = 0; i<RX_PDU_CNT; i++) {
		if(PduId == Rx_Pdu_Ids[i]) {
			return 1;
		}
	}
	return 0;
}


Std_ReturnType PduR_INF_RouteTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {

	Std_ReturnType result = E_OK;
	PduIdType PduHandleId;

	//Pointer to routing paths
	PduRRoutingPath_type** routes = PduRConfig->RoutingPaths;
	if (routes[0] == NULL) {
		//ERROR
		return E_NOT_OK;
	}

	/*printf("\nPduR_INF_RouteTransmit with payload: %s", PduInfoPtr->SduDataPtr);
	printf("\nPduR_INF_RouteTransmit with PduID: %d\n", TxPduId);*/

	//Query routing paths for target path
	for (uint8_t i = 0; routes[i] != NULL; i++) {
		if (routes[i]->PduRSrcPduRef->SourcePduHandleId == TxPduId) {
#if PDUR_CANIF_SUPPORT == STD_ON && PDUR_COM_SUPPORT == STD_ON

			/*if (Is_Pdu_Tx(TxPduId)) { 
				printf("PDUR Sending to COM\n");
				printf("ID: %d\n", TxPduId);
				printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
				printf("----------------------------------\n");
			}
			if (Is_Pdu_Rx(TxPduId)) {
				printf("PDUR Sending to CANIF\n");
				printf("ID: %d\n", TxPduId);
				printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
				printf("----------------------------------\n");
			}*/

			//Sending path
			if (Is_Pdu_Tx(TxPduId) && CanIf_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK) {
				UARTprintf("debug0\n");
				result |= CanIf_Transmit(PduHandleId, PduInfoPtr);
			}
				
			//Receiving path
			else if (Is_Pdu_Rx(TxPduId) && Com_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK) {
				Com_RxIndication(PduHandleId, PduInfoPtr);
			}
			else {
				printf("Error in PduR_INF_RouteTransmit");
				result = E_NOT_OK;
			}

				//result |= CanIf_Transmit(TxPduId, PduInfoPtr);

#endif
				return result;
		}
	}
	return E_NOT_OK;
}

/* ========================================================================== */
/*                          LOWER LAYER - CANIF MODULE                        */
/* ========================================================================== */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_CANIF_SUPPORT == STD_ON)
/*
  Description:  CanIF module confirms the transmission of a PDU
  Parameters:   TxPduId => The ID of the transmitted PDU,
								result => Transmission result
  Return Value: Nothing
*/
/*
void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result) {
	PduR_INF_TxConfirmation(TxPduId, result);
}*/

/*
  Description:  Indication of a received PDU from a CanIF module
  Parameters:   RxPduId     => The ID of the received PDU,
				PduInfoPtr  => The length and data of the received PDU
  Return Value: Nothing
*/
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType * PduInfoPtr) {
	//PduR_INF_RxIndication(RxPduId, PduInfoPtr);
	/*printf("PDUR Received PDU from CANIF\n");
	printf("ID: %d\n", RxPduId);
	printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
	printf("----------------------------------\n");*/

	UARTprintf("Message arrived to PduR, CanId: %d, Length: %d, Data: ",
			RxPduId, PduInfoPtr->SduLength);
	for(int i=0; i<PduInfoPtr->SduLength; i++) {
		UARTprintf("%02X ", PduInfoPtr->SduDataPtr[i]);
	}
	UARTprintf("\n");	
	
	PduR_INF_RouteTransmit(RxPduId, PduInfoPtr);
}
#endif

/*
void PduR_INF_TxConfirmation(PduIdType PduId, Std_ReturnType result) {
	//Pointer to routing paths
	PduRRoutingPath_type** routes = PduRConfig->RoutingPaths;
	if (routes[0] == NULL) {
		//ERROR
		return;
	}
	//Query routing paths for target path
	for (uint8_t i = 0; routes[i] != NULL; i++) {
		if (routes[i]->PduRDestPduRef->DestPduHandleId == PduId) {
			PduR_INF_RouteTxConfirmation(PduId, result);
			return;
		}
	}
}
void PduR_INF_RouteTxConfirmation(const PduRRoutingPath_type * route, Std_ReturnType result) {
	PduIdType PduHandleId;
#if PDUR_COM_SUPPORT == STD_ON
	if (Com_INF_GetPduHandleId(route->PduRSrcPduRef->SrcPduRef, &PduHandleId) == E_OK) {
		Com_TxConfirmation(PduHandleId, result);
	}
#endif
}*/

/*
void PduR_INF_RxIndication(PduIdType pduId, const PduInfoType* pduInfoPtr) {
	//Pointer to routing paths
	PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
	if (routes[0] == NULL) {
		//ERROR
		return;
	}
	//Query routing paths for target path
	for (uint8_t i = 0; routes[i] != NULL; i++) {
		if (routes[i]->PduRSrcPduRef->SourcePduHandleId == pduId) {
			PduR_INF_RouteRxIndication(routes[i]->PduRDestPduRef, pduInfoPtr);
			return;
		}
	}
}
void PduR_INF_RouteRxIndication(const PduRDestPdu_type *destination, const PduInfoType *PduInfo) {
	PduIdType PduHandleId;
	UARTprintf("Message arrived to PduR, CanId: %d, Length: %d, Data: ",
			destination->DestPduHandleId, PduInfo->SduLength);
	for(int i=0; i<PduInfo->SduLength; i++) {
		UARTprintf("%02X ", PduInfo->SduDataPtr[i]);
	}
	UARTprintf("\n");
  #if PDUR_COM_SUPPORT == STD_ON
	if (Com_INF_GetPduHandleId(destination->DestPduRef, &PduHandleId) == E_OK) {
	//if (com2pdur) { com2pdur = false; Com_RxIndication(pduId, PduInfo); }
		Com_RxIndication(PduHandleId, PduInfo);
		return;
	}
	#endif
	#if PDUR_CANIF_SUPPORT == STD_ON
	//else{
	//??
	//if (CanIf_INF_GetPduHandleId(destination->DestPduRef, &PduHandleId) == E_OK) {
	//Std_ReturnType retVal = CanIf_Transmit(PduHandleId, PduInfo);
	//}
	Std_ReturnType retVal = CanIf_Transmit(destination->DestPduHandleId, PduInfo);
	if (retVal != E_OK) {
		//raise an error
	}
	//}
	//printf("CanIf_Transmit2");
	//}
	#endif
}
*/