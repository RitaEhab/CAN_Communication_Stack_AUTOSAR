/*
 * PduR_PBcfg.c
 *
 *  Created on: Apr 21, 2020
 *      Author: Rita
 */

#include "PduR.h"
#include "PduR_Cfg.h"

PduInfoType PduInfoSrc = {
	.SduLength = 8
};

PduInfoType PduInfoDest = {
	.SduLength = 8
};

/* TRANSMISSION FROM COM TO CANIF
 * TRANSMISSION ID = 4
 * SRC: COM
 * DST: CANIF
 * SRC & DST BOTH HAVE SAME ID
 */

PduRSrcPdu PduRSrcPdu_Com_To_CanIf = {
	.PduRSourcePduHandleId = 4,
	.PduRSrcPduUpTxConf = TRUE,
	.PduRSrcPduRef = &PduInfoSrc
};

PduRDestPdu PduRDestPdu_Com_To_CanIf = {
	.pduRDestPduDataProvision = PDUR_DIRECT,
	.PduRDestPduHandleId = 4,
	.PduRTransmissionConfirmation = TRUE,
	.PduRDestPduRef = &PduInfoDest
};


/* RECEPTION FROM CANIF TO COM
 * RECEPTION ID = 3
 * SRC: CANIF
 * DST: COM
 * SRC & DST BOTH HAVE SAME ID
 */

PduRSrcPdu PduRSrcPdu_CanIf_To_Com = {
	.PduRSourcePduHandleId = 3,
	.PduRSrcPduUpTxConf = TRUE,
	.PduRSrcPduRef = &PduInfoSrc
};

PduRDestPdu PduRDestPdu_CanIf_To_Com = {
	.pduRDestPduDataProvision = PDUR_DIRECT,
	.PduRDestPduHandleId = 3,
	.PduRTransmissionConfirmation = TRUE,
	.PduRDestPduRef = &PduInfoDest
};

PduRRoutingPaths PDURRoutingPaths[] = {
	{
		/* TRANSMISSION FROM COM TO CANIF */
		.PduRConfigurationId = 0,
		.PduRSrcPduRRef = &PduRSrcPdu_Com_To_CanIf,
		.PduRDestPduRRef = &PduRDestPdu_Com_To_CanIf
	},
	{
		/* RECEPTION FROM CANIF TO COM */
		.PduRConfigurationId = 1,
		.PduRSrcPduRRef = &PduRSrcPdu_CanIf_To_Com,
		.PduRDestPduRRef = &PduRDestPdu_CanIf_To_Com
	}
};

PduR_PBConfigType pduR_PBConfigType = {
	.pduRRoutingPaths = &PDURRoutingPaths
};

/* ARRAY OF STRUCT FOR MAPPING IDS FROM PDUR AND CANIF
 * INDEX OF ARRAY = CANIF_PDU_ID
 * MEMBER OF STRUCT = PDUR_PDU_ID
 * */
PDU_PDUR_MAP PDU_CANIF_PDUR[] = {
	{
		// CANIF_ID = 0
	},
	{
		// CANIF_ID = 1
	},
	{
		// CANIF_ID = 2
		.PDUR_PDU_ID = 3
	},
	{
		// CANIF_ID = 3
		.PDUR_PDU_ID = 4
	},
	{
		// CANIF_ID = 4
	}
};

/* ARRAY OF STRUCT FOR MAPPING IDS FROM COM AND PDUR
 * INDEX OF ARRAY = PDUR_PDU_ID
 * MEMBER OF STRUCT = COM_PDU_ID
 * */
PDU_COM_MAP PDU_PDUR_COM[] = {
	{
		//	PDUR_ID = 0
	},
	{
		//	PDUR_ID = 1
	},
	{
		//	PDUR_ID = 2
	},
	{
		//	PDUR_ID = 3
		.COM_PDU_ID = 10
	},
	{
		//	PDUR_ID = 4
		.COM_PDU_ID = 20
	}
};
