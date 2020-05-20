#include "PduR.h"
#include "PduR_Cfg.h"

PduInfoType PduInfoSrc = {
	.SduLength = 8
};

PduInfoType PduInfoDest = {
	.SduLength = 8
};

/* TRANSMISSION FROM COM TO CANIF
 * SRC: COM (20)
 * DST: CANIF (3)
 */

PduRSrcPdu PduRSrcPdu_Com_To_CanIf = {
	.PduRSourcePduHandleId = 20,
	.PduRSrcPduUpTxConf = TRUE,
	.PduRSrcPduRef = &PduInfoSrc
};

PduRDestPdu PduRDestPdu_Com_To_CanIf = {
	.pduRDestPduDataProvision = PDUR_DIRECT,
	.PduRDestPduHandleId = 3,
	.PduRTransmissionConfirmation = TRUE,
	.PduRDestPduRef = &PduInfoDest
};


/* RECEPTION FROM CANIF TO COM
 * SRC: CANIF (2)
 * DST: COM (10)
 */

PduRSrcPdu PduRSrcPdu_CanIf_To_Com = {
	.PduRSourcePduHandleId = 2,
	.PduRSrcPduUpTxConf = TRUE,
	.PduRSrcPduRef = &PduInfoSrc
};

PduRDestPdu PduRDestPdu_CanIf_To_Com = {
	.pduRDestPduDataProvision = PDUR_DIRECT,
	.PduRDestPduHandleId = 10,
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

const PduR_PBConfigType pduR_PBConfigType = {
	.pduRRoutingPaths = &PDURRoutingPaths
};
