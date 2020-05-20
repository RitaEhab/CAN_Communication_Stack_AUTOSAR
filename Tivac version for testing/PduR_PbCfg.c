#include "PduR.h"
#include "Std_Types.h"



Pdu_Type Pdus[] = {
	{
		.PduLength = 8
	},
	{
		.PduLength = 8
	},
};

// Tx pdu IDs
const uint32 Tx_Pdu_Ids[TX_PDU_CNT] = {PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_0};

// Rx pdu IDs
const uint32 Rx_Pdu_Ids[RX_PDU_CNT] = {PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1};

//PDU transmission from COM module to CANIF module
//Source (COM):
PduRSrcPdu_type PduR_Message_0_Src = {
   .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_0,
   .SrcPduRef = &Pdus[0]
};

//Destination (CANIF):
PduRDestPdu_type PduR_Message_0_Dest = {
   .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_0,
   .DestPduRef = &Pdus[0]
};

//Routing path:
PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message0 = {
   .PduRSrcPduRef = &PduR_Message_0_Src,
   .PduRDestPduRef = &PduR_Message_0_Dest
};


//PDU reception from CANIF module to COM module
//Source (CANIF):
PduRSrcPdu_type PduR_Message_1_Src = {
   .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
   .SrcPduRef = &Pdus[1]
};

//Destination (COM):
PduRDestPdu_type PduR_Message_1_Dest = {
   .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
   .DestPduRef = &Pdus[1]
};

//Routing path:
PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1 = {
   .PduRSrcPduRef = &PduR_Message_1_Src,
   .PduRDestPduRef = &PduR_Message_1_Dest
};

PduRRoutingPath_type * RoutingPaths[] = {
   &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message0,
   &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1,
   NULL
};

PduR_PBConfigType PBPduRConfig = {
	.PduRConfigurationId = 0,
	.PduRMaxRoutingPathCnt = 2,
	.RoutingPaths = RoutingPaths
};