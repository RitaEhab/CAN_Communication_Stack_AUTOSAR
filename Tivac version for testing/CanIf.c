
#include "CanIf.h"
#include "CanIf_Cbk.h"
//file to be created by PDUR and Used Here
#include "PduR_CanIf.h"
#include "stdio.h"
#include "C:\Keil\Labware\utils\uartstdio.h"
#include "Can_CanIf.h"

//extern bool com2pdur = false;

//---------------------------------------------------------------------------

CanIf_ControllerModeType currentControllerMode;
const CanIf_ConfigType *canIf_ConfigPtr;

//-----------------------------------------------------------------------------------------

/*
in: ConfigPtr Pointer to configuration parameter set, used e.g. for post build parameters
This service Initializes internal and external interfaces of the CAN Interface for the further processing.
 */

void CanIf_Init(const CanIf_ConfigType *ConfigPtr) {
	/** When function CanIf_Init() is called, CanIf shall initialize
		every Transmit L-PDU Buffer assigned to CanIf.
	 */
	if (ConfigPtr != 0) {
		canIf_ConfigPtr = ConfigPtr;
		currentControllerMode = CANIF_CS_UNINIT;
	}
	else {
		printf("CanIf_Init fn -> ConfigPtr = NULL");
	}

	// for(uint8 i=0; i<CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT; i++){
	//     CanIf_SetPduMode(i, CANIF_OFFLINE);
	// }
}

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, CanIf_ControllerModeType *ControllerModePtr) {
	if (canIf_ConfigPtr == 0 || ControllerModePtr == 0) {
		return E_NOT_OK;
	}
	ControllerModePtr = &currentControllerMode;
	return E_OK;
}

//-----------------------------------------------------------------------------
//initiates a transition to the requested CAN controller mode ControllerMode of the CAN controller
// which is assigned by parameter ControllerId.
/*
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode) {
	if (ControllerMode == currentControllerMode) {
		printf("Already in This State");
		return E_OK;
	}
	switch (ControllerMode) {
		case CANIF_CS_SLEEP:
			if (currentControllerMode == CANIF_CS_STOPPED) {
				if (Can_SetControllerMode(ControllerId, CAN_T_SLEEP) == CAN_OK) {
					currentControllerMode = CANIF_CS_SLEEP;
					printf("current Controller mode is CANIF_CS_SLEEP");
					return E_OK;
				} else {
					return E_NOT_OK;
				}
			}
			break;
		case CANIF_CS_STARTED:
			if (currentControllerMode == CANIF_CS_STOPPED) {
				if (Can_SetControllerMode(ControllerId, CAN_T_START) == CAN_OK) {
					currentControllerMode = CANIF_CS_STARTED;
					printf("current Controller mode is CANIF_CS_STARTED");
					return E_OK;
				} else
					return E_NOT_OK;
			}
			break;
		case CANIF_CS_STOPPED:
			if (currentControllerMode == CANIF_CS_STARTED) {
				if (Can_SetControllerMode(ControllerId, CAN_T_STOP) == CAN_OK) {
					currentControllerMode = CANIF_CS_STOPPED;
					printf("current Controller mode is CANIF_CS_STOPPED");
					return E_OK;
				} else
					return E_NOT_OK;
			} else if (currentControllerMode == CANIF_CS_SLEEP) {
				if (Can_SetControllerMode(ControllerId, CAN_T_WAKEUP) == CAN_OK) {
					currentControllerMode = CANIF_CS_STOPPED;
					printf("current Controller mode is CANIF_CS_STOPPED");
					return E_OK;
				} else
					return E_NOT_OK;
			}
			break;
		case CANIF_CS_UNINIT:
			printf("CanIf_SetControllerMode : CANIF_CS_UNINIT case");
			break;
			break;
		default:
			printf("CanIf_SetControllerMode : default case");
			break;
	}
	return E_OK;
}
 */
 //-----------------------------------------------------------------------------

Std_ReturnType CanIf_INF_GetPduHandleId(Pdu_Type* Pdu, PduIdType* PduHandleIdPtr) {
	Std_ReturnType Std_Ret = E_NOT_OK;
  uint32 i = 0;
	for (i = 0; i < canIf_ConfigPtr->canIfInitCfg->canIfMaxTxPduCfg; ++i) {
		if (canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg[i].canIfTxPduRef == Pdu) {
			Std_Ret = E_OK;
			*PduHandleIdPtr = canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg[i].canIfTxPduId;
		}
	}
	return Std_Ret;
}

/*
CanIfTxSduId L-SDU handle to be transmitted.This handle specifies the corresponding CAN L-SDU ID and
implicitly the CAN Driver instance as well as the corresponding CAN controller device.
CanIfTxInfoPtr Pointer to a structure with CAN L-SDU related data: DLC and pointer to
CAN L-SDU buffer including the MetaData of dynamic L-PDUs.
This service initiates a request for transmission of the CAN L-PDU specified by the CanTxSduId and CAN related
data in the L-SDU structure.
 */

Std_ReturnType CanIf_Transmit(PduIdType CanIfTxSduId, const PduInfoType *CanIfTxInfoPtr) {

	/*printf("CANIF Received PDU from PDUR\n");
	printf("ID: %d\n", CanIfTxSduId);
	printf("MSG: %s\n", CanIfTxInfoPtr->SduDataPtr);
	printf("----------------------------------\n");*/
	
	UARTprintf("CanIf got a message; Id: %d, Length: %d, Data: ", 
							CanIfTxSduId, CanIfTxInfoPtr->SduLength);
	int i=0;
	for(i=0; i<CanIfTxInfoPtr->SduLength; i++) {
		UARTprintf("%02X ", CanIfTxInfoPtr->SduDataPtr[i]);
	}
	UARTprintf("\n");
	
	if (canIf_ConfigPtr == 0 || CanIfTxInfoPtr == 0) {
		//printf("CanIf_Transmit : CanIF is not initialized or no Data sent");
		return E_NOT_OK;
	}
	//printf("\n%u\n", CanIfTxSduId);
	//TTTT
	
	//const CanIfTxPduCfg *txEntry = (CanIfTxPduCfg *)(&canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg[CanIfTxSduId]);
	//prepare the PDU data
	Can_PduType canPdu;
	
	//canPdu.id = (CanIfTxSduId & (uint32)0xFFFFF000) >> 12;
	//canPdu.id = txEntry->canIfTxPduCanId;
	canPdu.id = canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg->canIfTxPduCanId;

	
	canPdu.length = CanIfTxInfoPtr->SduLength;
	canPdu.sdu = CanIfTxInfoPtr->SduDataPtr;
	
	//canPdu.swPduHandle = CAN_IF_ID;
	canPdu.swPduHandle = CanIfTxSduId;
	
	
	//uint8 hth = (CanIfTxSduId & (uint32)0x00000FF0) >> 4;
	//uint8 hth = txEntry->canIfTxPduBufferRef->canIfBufferHthRef->canIfHthIdSymRef->canObjectId;
	uint8 hth = canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg->canIfTxPduBufferRef->canIfBufferHthRef->canIfHthIdSymRef->canObjectId;
	
	//printf("\nCanIf_Transmit with payload: %s", canPdu.sdu);
	//printf("\nCanIf_Transmit with PduID: %d", CanIfTxSduId);
	//printf("\nInterface ID: %d, msgId: %d, hth: %d\n", canPdu.swPduHandle, canPdu.id, hth);

	Can_ReturnType retVal = Can_Write(hth, &canPdu);
	
	if (retVal == CAN_NOT_OK || retVal == CAN_BUSY) {
		return E_NOT_OK;
	}
	return E_OK;

}

/*
in : CanTxPduId L-PDU handle of CAN L-PDU successfully transmitted.This ID specifies the corresponding CAN L-PDU ID
				and implicitly the CAN Driver instance as well as the corresponding CAN controller device.
This service confirms a previously successfully processed transmission of a CAN TxPDU.
 */

 //for now set CanTxPduID to zero
void CanIf_TxConfirmation(PduIdType CanTxPduId) {
	if (canIf_ConfigPtr == 0) {
		printf("CanIf_TxConfirmation : The CanIf is not initialized");
		return;
	}
	if (CanTxPduId > canIf_ConfigPtr->canIfInitCfg->canIfMaxTxPduCfg) {
		printf("CanIf_TxConfirmation : exceeded THE MAX Number of IDs");
		return;
	}
	CanIfTxPduCfg *TxPduCfgPtr = (CanIfTxPduCfg *)(&canIf_ConfigPtr->canIfInitCfg->canIfTxPduCfg[CanTxPduId]);

	//    if (TxPduCfgPtr == null) {
	//        printf("CanIf_TxConfirmation : TxPduCfgPtr = NULL ");
	//        return;
	//    }

	(TxPduCfgPtr->canIfTxPduUserTxConfirmationName)(CanTxPduId);
}

/*
in : Mailbox Identifies the HRH and its corresponding CAN Controller
	 PduInfoPtr Pointer to the received L-PDU
This service indicates a successful reception of a received CAN Rx L-PDU to the CanIf after passing all filters and validation checks.
 */

static CanIfRxPduCfg *findRxPduCfg(Can_HwHandleType Hoh) {
	uint32 i=0;
	for ( i = 0; i != canIf_ConfigPtr->canIfInitCfg->canIfMaxRxPduCfg; ++i) {
		CanIfRxPduCfg *rxEntry = &canIf_ConfigPtr->canIfInitCfg->canIfRxPduCfg[i];
		if (Hoh == rxEntry->canIfRxPduHrhIdRef->canIfHrhIdSymRef->canObjectId) {
			return (CanIfRxPduCfg * const)(&canIf_ConfigPtr->canIfInitCfg->canIfRxPduCfg[i]);
		}
	}
	return 0;
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr) {
	//Printing data coming to CanIf to UART
	UARTprintf("Message arrived to CanIf, CanId: %d, ControllerId: %d, Hoh: %d, Length: %d, Data: ", 
		Mailbox->CanId, Mailbox->ControllerId, Mailbox->Hoh, PduInfoPtr->SduLength);
	int i=0;
	for(i=0; i<PduInfoPtr->SduLength; i++) {
		UARTprintf("%02X ", PduInfoPtr->SduDataPtr[i]);
	}
	UARTprintf("\n");

	/*printf("CANIF Sending PDU to PDUR\n");
	printf("ID: %d\n", Mailbox->CanId);
	printf("MSG: %s\n", PduInfoPtr->SduDataPtr);
	printf("----------------------------------\n");*/
	
	const CanIfRxPduCfg *RxPduCfgPtr;
	CanIf_PduModeType PduMode;
	PduIdType RxPduId;
	RxPduCfgPtr = findRxPduCfg(Mailbox->Hoh);
	if (RxPduCfgPtr == 0) {
		///report development error code CANIF_E_PARAM_HOH to the Det
		return;
	}
	
	//??
	/*
	if (PduInfoPtr->SduLength != RxPduCfgPtr->canIfRxPduDlc) {
		///report development error code CANIF_E_INVALID_DATA_LENGTH to the Det
		return;
	}*/
	
	(RxPduCfgPtr->canIfRxPduUserRxIndicationName)(RxPduCfgPtr->CanIfRxPduId, PduInfoPtr);
	//PduR_CanIfRxIndication(RxPduCfgPtr->CanIfRxPduId, PduInfoPtr);

	if (Mailbox == 0 || PduInfoPtr == 0) {
		///Report an error CANIF_E_PARAM_POINTER to the Det_ReportError
		return;
	}


	uint32_t Id = Mailbox->CanId;
	//Id = Id << 16 | (Mailbox->Hoh) << 8;

	//com2pdur = true;

	// | ((Mailbox->Hoh) << 8) | ((Mailbox->ControllerId) << 4);
	//PduR_INF_RouteRxIndication(Id, PduInfoPtr);
}