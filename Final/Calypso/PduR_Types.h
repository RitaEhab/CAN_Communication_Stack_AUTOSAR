#ifndef PDUR_TYPES_H_INCLUDED
#define PDUR_TYPES_H_INCLUDED

#include "ComStack_Types.h"

typedef uint16 PduR_PBConfigIdType;

typedef enum PduR_StateType{
  PDUR_UNINIT,
  PDUR_ONLINE
}PduR_StateType;

typedef enum PduRDestPduDataProvision {
	PDUR_DIRECT,		//  call the transmit function in the destination module and not buffer the I-PDU
	PDUR_TRIGGERTRANSMIT	// The dest module will request the I-PDU using the triggerTransmit function
} PduRDestPduDataProvision;

typedef struct {
	PduIdType PduRSourcePduHandleId;	// PDU identifier assigned by PDU Router
	boolean PduRSrcPduUpTxConf;	// When enabled, the TxConfirmation will be forwarded to the upper layer
	PduInfoType *PduRSrcPduRef;	// ref to unique PDU id which shall be used for the requested PDUR operation
} PduRSrcPdu;

typedef struct {
	PduRDestPduDataProvision pduRDestPduDataProvision;
	PduIdType PduRDestPduHandleId;		// PDU id assigned by PDUR. Used by communication interface
	boolean PduRTransmissionConfirmation;	// PduR to know when all modules have confirmed a multicast operation
	PduInfoType *PduRDestPduRef;	// ref to unique PDU identifier that will be used instead of src PDU id
} PduRDestPdu;

typedef struct{
	PduR_PBConfigIdType PduRConfigurationId;			// Id can be read using the PduR API
	PduRSrcPdu *PduRSrcPduRRef;
	PduRDestPdu *PduRDestPduRRef;
}PduRRoutingPaths;

typedef struct {
	PduRRoutingPaths *pduRRoutingPaths;
} PduR_PBConfigType;

#endif // PDUR_TYPES_H_INCLUDED
