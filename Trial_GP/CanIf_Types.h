/*
 * CanIf_Types.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CANIF_TYPES_H_
#define CANIF_TYPES_H_

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"


/* The PduMode of a channel defines its transmit or receive activity */
typedef enum CanIf_PduModeType{
	CANIF_OFFLINE = 0x00,
	CANIF_TX_OFFLINE = 0x01,
	CANIF_TX_OFFLINE_ACTIVE = 0x02,
	CANIF_ONLINE = 0x03
} CanIf_PduModeType;

/* CAN L-PDU notification status */
typedef enum CanIf_NotifStatusType{
	CANIF_TX_RX_NOTIFICATION = 0x01 ,
	CANIF_NO_NOTIFICATION = 0x00
} CanIf_NotifStatusType;

typedef enum CanIfPrivateSoftwareFilterType {
	BINARY,
	INDEX,
	LINEAR,
	TABLE
}CanIfPrivateSoftwareFilterType;

typedef enum CanIfPublicHandleTypeEnum{
	UINT16,
	UINT8
} CanIfPublicHandleTypeEnum;

typedef enum CanIfTxPduCanIdType{
	EXTENDED_CAN,
	EXTENDED_FD_CAN,
	STANDARD_CAN,
	STANDARD_FD_CAN
} CanIfTxPduCanIdType;

typedef enum CanIfTxPduType{
	Dynamic,
	Static						// Edited to lower case to avoid conflict with STATIC keyword
} CanIfTxPduType;

typedef enum CanIfTxPduUserTxConfirmationUL{
	CAN_NM,
	CAN_TP,
	CAN_TSYN,					// Global Time Synchronization over CAN
	CDD,						// Complex Driver
	J1939NM,
	J1939TP,
	PDUR,						// PDU Router
	XCP							// Extended Calibration Protocol
} CanIfTxPduUserTxConfirmationUL;

typedef enum CanIfRxPduCanIdType{
	EXTENDED_CAN,
	EXTENDED_FD_CAN,
	EXTENDED_NO_FD_CAN,
	STANDARD_CAN,
	STANDARD_FD_CAN,
	STANDARD_NO_FD_CAN
} CanIfRxPduCanIdType;

typedef enum CanIfRxPduUserRxIndicationUL{
	CAN_NM,
	CAN_TP,
	CAN_TSYN,					// Global Time Synchronization over CAN
	CDD,						// Complex Driver
	J1939NM,
	J1939TP,
	PDUR,						// PDU Router
	XCP							// Extended Calibration Protocol
} CanIfRxPduUserRxIndicationUL;

typedef enum CanIf_StateType{
	CANIF_READY,
	CANIF_UNINIT
} CanIf_StateType;

typedef struct {
	 CanIfPrivateSoftwareFilterType canIfPrivateSoftwareFilterType ;
	 CanIf_NotifStatusType	canIf_NotifStatusType ;
}CanIfPrivateCfg;

/* This container contains the Tx buffer configuration */
typedef struct {
	/* the number of CanIf Tx L-PDUs which can be buffered in one Tx buffer */
	uint8 CanIfBufferSize; // #if CanIfPublicTxBuffering == STD_OFF >> this param = 0 for 'ALL' tx buffer
						   // #if hth == FULL >> this param = 0 for 'THIS' tx buffer
	//CanIfBufferHthRef * canIfBufferHthRef = &CanIfHthCfg;  		HABD EL SENIN!!

} CanIfBufferCfg;

typedef struct{
	uint8 canIfDevErrorDetect;
	uint8 CanIfMetaDataSupport;
	uint8 CanIfPublicCancelTransmitSupport;
	uint8 * CanIfPublicCddHeaderFile;
	CanIfPublicHandleTypeEnum canIfPublicHandleTypeEnum;
	uint8 CanIfPublicIcomSupport;
	uint8 CanIfPublicMultipleDrvSupport;
	uint8 CanIfPublicPnSupport;
	uint8 CanIfPublicReadRxPduDataApi;				// TO BE DELETED AS IT IS PRE-COMPILED
	uint8 CanIfPublicReadRxPduNotifyStatusApi;
	uint8 CanIfPublicReadTxPduNotifyStatusApi;
	uint8 CanIfPublicSetDynamicTxIdApi;
	uint8 CanIfPublicReadRxPduNotifyStatusApi;
	uint8 CanIfPublicReadTxPduNotifyStatusApi;
	uint8 CanIfPublicSetDynamicTxIdApi;
	uint8 CanIfPublicTxBuffering;
	uint8 CanIfPublicTxConfirmPollingSupport;
	uint8 CanIfPublicWakeupCheckValidByNM;
	uint8 CanIfTxOfflineActiveSupport;
}CanIfPublicCfg;


typedef struct {
	uint8 CanIfTxPduCanId ;
	uint16 CanIfTxPduCanIdMask;
	CanIfTxPduCanIdType canIfTxPduCanIdType;
	uint8 CanIfTxPduId;
	uint8 CanIfTxPduPnFilterPdu;
	uint8 CanIfTxPduReadNotifyStatus;
	uint8 CanIfTxPduTriggerTransmit;
	uint8 CanIfTxPduTruncation;
	CanIfTxPduType canIfTxPduType;
	CanIfBufferCfg *CanIfTxPduBufferRef;
	// Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
	// PDU_TYPE *CanIfTxPduRef;					WHAT IS GLOBAL PDU STRUCTURE?
}CanIfTxPduCfg;

/* This container contains the configuration (parameters) of each receive CAN L-PDU. */
typedef struct{
	/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface */
	uint16 CanIfRxPduCanId;
	/* Identifier mask which denotes relevant bits in the CAN Identifier. */
	uint16 CanIfRxPduCanIdMask;
	/* CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-PDU reception */
	CanIfRxPduCanIdType canIfRxPduCanIdType;
	/* Data length of the received CAN L-PDUs used by the CAN Interface */
	uint8 CanIfRxPduDataLength;
	/* ECU wide unique, symbolic handle for receive CAN L-SDU */
	uint16 CanIfRxPduId;
	/* Enables and disables the Rx buffering for reading of received L-SDU data */
	uint8 CanIfRxPduReadData;
	/* Enables and disables receive indication for each receive CAN L-SDU for reading its notification status */
	uint8 CanIfRxPduReadNotifyStatus;
	/* Reference to the HRH to which Rx L-PDU belongs to */
	//CanIfHrhCfg *CanIfRxPduHrhIdRef; 					TO BE ADDED
	// Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack
	// PDU_TYPE *CanIfRxPduRef;					WHAT IS GLOBAL PDU STRUCTURE?
} CanIfRxPduCfg;

/*  This container contains the configuration (parameters) of an adressed
	CAN controller by an underlying CAN Driver module */
typedef struct {
	/*  Each controller shall be assigned to one specific ControllerId of the CanIf */
	const uint8 CanIfCtrlId;
	/*  This parameter defines if a respective controller of the referenced CAN
		Driver modules is queriable for wake up events*/
	boolean CanIfCtrlWakeupSupport;
	/*  This parameter references to the logical handle of the underlying CAN
		controller from the CAN Driver module to be served by the CAN
		Interface module */
	void *CanIfCtrlCanCtrlRef;
} CanIfCtrlCfg;

typedef struct {
	/*Selects the CAN Interface specific configuration setup. This type of the
	external data structure shall contain the post build initialization data for
	the CAN Interface for all underlying CAN Dirvers.*/
	const uint8 *canIfInitCfgSet;
	// Maximum Total size of all Tx buffers
	const uint32 canIfMaxBufferSize;
	// Maximum number of Pdus.
	const uint32 canIfMaxRxPduCfg;
	// Maximum number of Pdus.
	const uint32 canIfMaxTxPduCfg;
	// this Container Contains The Txbuffer Configuration
	//const CanIfBufferCfg *canIfBufferCfg;
	//This container contains the references to the configuration setup of each underlying CAN Driver.
	//const CanIfInitHohCfg *canIfInitHohCfg;
	//This container contains the configuration (parameters) of each receive CAN L-PDU.
	//CanIfRxPduCfg *canIfRxPduCfg;
	//This container contains the configuration (parameters) of a transmit CAN L-PDU
	//CanIfTxPduCfg *canIfTxPduCfg;
} CanIfInitCfg;

/* initialization data structure */
typedef struct {

} CanIf_ConfigType;


#endif /* CANIF_TYPES_H_ */
