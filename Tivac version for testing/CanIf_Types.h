#ifndef CANIF_TYPES_H_INCLUDED
#define CANIF_TYPES_H_INCLUDED

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
	RX_EXTENDED_CAN,
	RX_EXTENDED_FD_CAN,
	RX_EXTENDED_NO_FD_CAN,
	RX_STANDARD_CAN,
	RX_STANDARD_FD_CAN,
	RX_STANDARD_NO_FD_CAN
} CanIfRxPduCanIdType;

typedef enum CanIfRxPduUserRxIndicationUL{
	RX_CAN_NM,
	RX_CAN_TP,
	RX_CAN_TSYN,					// Global Time Synchronization over CAN
	RX_CDD,						// Complex Driver
	RX_J1939NM,
	RX_J1939TP,
	RX_PDUR,						// PDU Router
	RX_XCP							// Extended Calibration Protocol
} CanIfRxPduUserRxIndicationUL;

typedef enum CanIf_StateType{
	CANIF_READY,
	CANIF_UNINIT
} CanIf_StateType;

/*  This container contains the configuration (parameters) of an adressed
	CAN controller by an underlying CAN Driver module */
typedef struct {
	/*  Each controller shall be assigned to one specific ControllerId of the CanIf */
	uint8 CanIfCtrlId;
	/*  This parameter defines if a respective controller of the referenced CAN
		Driver modules is queriable for wake up events*/
	boolean CanIfCtrlWakeupSupport;
	/*  This parameter references to the logical handle of the underlying CAN
		controller from the CAN Driver module to be served by the CAN
		Interface module (reference to CanController) */
	void *CanIfCtrlCanCtrlRef;
} CanIfCtrlCfg;

/* This container contains parameters related to each HTH */
typedef struct {
	CanIfCtrlCfg *CanIfHthCanCtrlIdRef;
	CanHardwareObject *CanIfHthIdSymRef;
} CanIfHthCfg;

/* This container contains parameters related to each HRH */
typedef struct {
	/*  Selects the hardware receive objects by using the HRH range/list from
		CAN Driver configuration to define, for which HRH a software filtering
		has to be performed at during receive processing */
	boolean CanIfHrhSoftwareFilter;
	/*  Reference to controller Id to which the HRH belongs to. A controller
		can contain one or more HRHs */
	CanIfCtrlCfg *CanIfHrhCanCtrlIdRef;
	/*  The parameter refers to a particular HRH object in the CanDrv configuration */
	CanHardwareObject *CanIfHrhIdSymRef;
} CanIfHrhCfg;

/*  This container contains the references to the configuration setup of
	each underlying CAN Driver */
typedef struct {
	CanIfHrhCfg *canIfHrhCfg;
	CanIfHthCfg *canIfHthCfg;
} CanIfInitHohCfg;

/* This container contains the Tx buffer configuration */
typedef struct {
	/* the number of CanIf Tx L-PDUs which can be buffered in one Tx buffer */
	uint8 CanIfBufferSize;

	/* Each HTH shall not be assigned to more than one buffer */
	CanIfHthCfg *canIfBufferHthRef;
} CanIfBufferCfg;


typedef struct {
	/* Reference to the Init Hoh Configuration */
	CanIfInitHohCfg *CanIfCtrlDrvInitHohConfigRef;
} CanIfCtrlDrvCfg;

typedef struct {
	/*  CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
		CAN L-PDU transmission */
	uint16 CanIfTxPduCanId ;
	/* Identifier mask which denotes relevant bits in the CAN Identifier */
	uint16 CanIfTxPduCanIdMask;
	/*  Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
		Driver module for CAN L-PDU transmission */
	CanIfTxPduCanIdType canIfTxPduCanIdType;
	/* ECU wide unique, symbolic handle for transmit CAN L-SDU */
	uint16 CanIfTxPduId;
	/*  If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
		could be configured which will pass the CanIfPnFilter */
	boolean CanIfTxPduPnFilterPdu;
	/*  Enables and disables transmit confirmation for each transmit CAN
		L-SDU for reading its notification status */
	boolean CanIfTxPduReadNotifyStatus;
	/* Determines if or if not CanIf shall use the trigger transmit API for this PDU */
	boolean CanIfTxPduTriggerTransmit;
	/* Enables/disables truncation of PDUs that exceed the configured size */
	boolean CanIfTxPduTruncation;
	/* Defines the type of each transmit CAN L-PDU */
	CanIfTxPduType canIfTxPduType;
	// CanIfTxPduUserTriggerTransmitName fakes! multiplicity=0
	/* reference to a CanIf buffer configuration */
	CanIfBufferCfg *CanIfTxPduBufferRef;
	/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack */
	PduInfoType *CanIfTxPduRef;
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
	boolean CanIfRxPduReadData;
	/* Enables and disables receive indication for each receive CAN L-SDU for reading its notification status */
	boolean CanIfRxPduReadNotifyStatus;
	/* Reference to the HRH to which Rx L-PDU belongs to */
	CanIfHrhCfg *CanIfRxPduHrhIdRef;
	// Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack
	PduInfoType *CanIfRxPduRef;
} CanIfRxPduCfg;


typedef struct {
	/*  Selects the CAN Interface specific configuration setup. This type of the
		external data structure shall contain the post build initialization data for
		the CAN Interface for all underlying CAN Drivers */
	const uint8 *canIfInitCfgSet;
	// Maximum Total size of all Tx buffers
	const uint32 canIfMaxBufferSize;
	// Maximum number of Pdus.
	const uint32 canIfMaxRxPduCfg;
	// Maximum number of Pdus.
	const uint32 canIfMaxTxPduCfg;
	// this Container Contains The Txbuffer Configuration
	const CanIfBufferCfg *canIfBufferCfg;
	//This container contains the references to the configuration setup of each underlying CAN Driver.
	const CanIfInitHohCfg *canIfInitHohCfg;
	//This container contains the configuration (parameters) of each receive CAN L-PDU.
	CanIfRxPduCfg *canIfRxPduCfg;
	//This container contains the configuration (parameters) of a transmit CAN L-PDU
	CanIfTxPduCfg *canIfTxPduCfg;
} CanIfInitCfg;

/* initialization data structure */
typedef struct {
	CanIfInitCfg *CanIf_InitCfg;
} CanIf_ConfigType;

#endif // CANIF_TYPES_H_INCLUDED
