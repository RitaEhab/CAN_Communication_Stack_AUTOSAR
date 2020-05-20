#ifndef COM_H_INCLUDED
#define COM_H_INCLUDED

#include "Com_Types.h"
#include "Com_Cfg.h"
#include "Com_Pbcfg.h"

#define COM_VENDOR_ID    			(31U)
#define COM_MODULE_ID    			(50U)
#define COM_INSTANCE_ID  			(0U)

/*	Module Version 1.0.0	*/
#define COM_SW_MAJOR_VERSION           (1U)
#define COM_SW_MINOR_VERSION           (0U)
#define COM_SW_PATCH_VERSION           (0U)

/******************************************************************************
 *                     	 API Service ID 	                                  *
 ******************************************************************************/

#define COM_INIT_SID             	(uint8)0x01
#define Com_SendSignal_SID          (uint8)0x0a
#define Com_ReceiveSignal_SID       (uint8)0x0b
#define Com_TriggerTransmit_SID     (uint8)0x41
#define Com_RxIndication_SID        (uint8)0x42
#define Com_TxConfirmation_SID      (uint8)0x40
#define Com_StartOfReception_SID    (uint8)0x46
#define Com_CopyRxData_SID          (uint8)0x44
#define Com_CopyTxData_SID       	(uint8)0x43

/*******************************************************************************
 *                      	DET ERRORS                                         *
 *******************************************************************************/
/* DEVELOPMENT ERRORS */
#define COM_E_PARAM                 (uint8)0x01
#define COM_E_UNINIT				(uint8)0x02
#define COM_E_PARAM_POINTER			(uint8)0x03
#define COM_E_INIT_FAILED			(uint8)0x04

/* RUNTIME ERRORS */
#define COM_E_SKIPPED_TRANSMISSION  (uint8)0x05

/*******************************************************************************
 *                      	Function Prototypes                                *
 *******************************************************************************/

/* MODULE INITIALIZATION */
void Com_Init( const Com_ConfigType* config );

/* COMMUINCATION SERVICES */
uint8 Com_SendSignal( Com_SignalIdType SignalId, const void* SignalDataPtr );

/* CALLBACK FUNCTIONS AND NOTIFICATIONS */
void Com_RxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr );
void Com_TxConfirmation( PduIdType TxPduId, Std_ReturnType result ); // FOR TESTING ONLY


#endif // COM_H_INCLUDED
