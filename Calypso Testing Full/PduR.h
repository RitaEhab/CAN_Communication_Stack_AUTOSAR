#ifndef PDUR_H_INCLUDED
#define PDUR_H_INCLUDED


#include "PduR_Types.h"
#include "PduR_Cfg.h"
#include "PduR_PBcfg.h"

#define PDUR_VENDOR_ID    			(31U)
#define PDUR_MODULE_ID    			(51U)
#define PDUR_INSTANCE_ID  			(0U)

/*	Module Version 1.0.0	*/
#define PDUR_SW_MAJOR_VERSION           (1U)
#define PDUR_SW_MINOR_VERSION           (0U)
#define PDUR_SW_PATCH_VERSION           (0U)


/******************************************************************************
 *                      	API Service ID 	                                  *
 ******************************************************************************/

#define PDUR_INIT_SID						(uint8)0xF0
#define	PDUR_CANIFRXINDICATION_SID			(uint8)0x42
#define	PDUR_CANIFTXCONFIRMATION_SID		(uint8)0x40
#define	PDUR_COMTRANSMIT_SID				(uint8)0x49

/*******************************************************************************
 *                      	DET ERRORS                                         *
 *******************************************************************************/

/* DEVELOPMENT ERRORS */
#define	PDUR_E_INIT_FAILED								(uint8)0x00
#define	PDUR_E_UNINIT									(uint8)0x01
#define	PDUR_E_PDU_ID_INVALID							(uint8)0x02
#define	PDUR_E_ROUTING_PATH_GROUP_ID_INVALID			(uint8)0x08
#define	PDUR_E_PARAM_POINTER							(uint8)0x09

/* RUNTIME ERRORS */
#define	PDUR_E_TP_TX_REQ_REJECTED						(uint8)0x03
#define	PDUR_E_PDU_INSTANCES_LOST						(uint8)0x0A

/*******************************************************************************
 *                      	Function Prototypes                                *
 *******************************************************************************/

/* MODULE INITIALIZATION */
void PduR_Init( const PduR_PBConfigType* ConfigPtr );

/* LOWER LAYER COMMUNICATION SERVICES */
void PduR_CanIfRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr );
void PduR_CanIfTxConfirmation( PduIdType TxPduId, Std_ReturnType result );

/* UPPER LAYER COMMUNICATION SERVICES */
Std_ReturnType PduR_ComTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr );

#endif // PDUR_H_INCLUDED
