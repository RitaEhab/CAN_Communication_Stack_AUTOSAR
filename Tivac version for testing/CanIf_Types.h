#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

typedef enum {
	CANIF_CS_UNINIT = 0, /* Default mode of each CAN controller after power on. */
	CANIF_CS_STOPPED, /* CAN controller is halted and does not operate on the network */
	CANIF_CS_STARTED, /* CAN controller is in full-operational mode.*/
	CANIF_CS_SLEEP /* CAN controller is in SLEEP mode and can be woken up by an internal (SW) request or by a network event */
} CanIf_ControllerModeType;

typedef enum {
	CANIF_NO_NOTIFICATION = 0, /* No transmit or receive event occurred for the requested L-PDU. */
	CANIF_TX_RX_NOTIFICATION /* The requested Rx/Tx CAN L-PDU was successfully transmitted or received. */
} CanIf_NotifStatusType;

typedef enum {
	CANIF_OFFLINE = 0, /* Transmit and receive path of the corresponding channel are disabled */
	CANIF_TX_OFFLINE, /* Transmit path of the corresponding channel is disabled. The receive path is enabled */
	CANIF_TX_OFFLINE_ACTIVE, /* Transmit path of the corresponding channel is in offline active mode. The receive path is disabled. CanIfTxOfflineActiveSupport = TRUE */
	CANIF_ONLINE /* Transmit and receive path of the corresponding channel are enabled */
} CanIf_PduModeType;

typedef enum {
	BINARY,
	INDEX,
	LINEAR,
	TABLE
} CanIfPrivateSoftwareFilterType;

typedef enum {
	UINT8,
	UINT16
} CanIfPublicHandleTypeEnum;

typedef enum {
	EXTENDED,
	STANDARD
} CanIfHrhRangeRxPduRangeCanIdType;

typedef enum {
	/** CAN 2.0 or CAN FD frame with extended identifier (29 bits) */
	EXTENDED_CAN,
	/** CAN FD frame with extended identifier (29 bits) */
	EXTENDED_FD_CAN,
	/** CAN 2.0 frame with extended identifier (29 bits) */
	EXTENDED_NO_FD_CAN,
	/** CAN 2.0 or CAN FD frame with standard identifier (11 bits)*/
	STANDARD_CAN,
	/** CAN FD frame with standard identifier (11 bits)*/
	STANDARD_FD_CAN,
	/** CAN 2.0 frame with standard identifier (11 bits)*/
	STANDARD_NO_FD_CAN

} CanIfPduCanIdType;

typedef enum {
	CAN_NM,
	CAN_TP,
	CAN_TSYN, ///Global Time Synchronization over CAN
	CDD,
	J1939NM,
	J1939TP,
	PDUR, //PDU Router
	XCP ///Extended Calibration Protocol

} CanIfRxPduUserRxIndicationULType;

/** Defines the type of each transmit CAN L-PDU */
typedef enum {
	DYNAMIC, ///CAN ID is defined at runtime.
	STATIC, ///CAN ID is defined at compile-time.
} CanIfTxPduType;

typedef void(*CanIfRxPduUserRxIndicationNameType)(PduIdType, const PduInfoType *);
typedef CanIfRxPduUserRxIndicationULType CanIfTxPduUserTxConfirmationUL;

typedef Std_ReturnType(*CanIfTxPduUserTriggerTransmitName)(PduIdType, PduInfoType *);

typedef void(*CanIfTxPduUserTxConfirmationName)(PduIdType);

typedef enum {
	CAN_SM, ///CAN State Manager
	_CDD ///Complex Driver
} CanIfDispatchUserCtrlBusOffULType;

typedef enum {
	ECUM, ///ECU State Manager
	CDD_ ///Complex Driver
} CanIfDispatchUserValidateWakeupEventULType;

/* ------------- CanIfDispatchCfgType Typedefs ------------- */
typedef void(*CanIfDispatchUserCheckTrcvWakeFlagIndicationName)(uint8);
typedef void(*CanIfDispatchUserClearTrcvWufFlagIndicationName)(uint8);
typedef void(*CanIfDispatchUserConfirmPnAvailabilityName)(uint8);
typedef void(*CanIfDispatchUserCtrlBusOffName)(uint8);
//typedef void (*CanIfDispatchUserCtrlModeIndicationName)(uint8, Can_ControllerStateType);
//typedef void (*CanIfDispatchUserTrcvModeIndicationName)(uint8, CanTrcv_TrcvModeType);
//typedef void (*CanIfDispatchUserValidateWakeupEventName)(EcuM_WakeupSourceType);
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserClearTrcvWufFlagIndicationUL;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserConfirmPnAvailabilityUL;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCtrlModeIndicationUL;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserTrcvModeIndicationUL;

typedef struct CanIfRxPduCanIdRange {
	// Lower CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids are mapped to one PduId
	uint32 CanIfRxPduCanIdRangeLowerCanId;
	// Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids are mapped to one PduId
	uint32 CanIfRxPduCanIdRangeUpperCanId;
} CanIfRxPduCanIdRange;

typedef struct CanIfCtrlCfg {
	/*  This parameter references to the logical handle of the underlying CAN
		controller from the CAN Driver module to be served by the CAN
		Interface module*/
	void *canIfCtrlCanCtrlRef;
	/*  This parameter abstracts from the CAN Driver specific parameter
		Controller. Each controller of all connected CAN Driver modules shall
		be assigned to one specific ControllerId of the CanIf.*/
	const uint8 canIfCtrlId;
	/*  This parameter defines if a respective controller of the referenced CAN
		Driver modules is queriable for wake up events.*/
	bool canIfCtrlWakeupSupport;
} CanIfCtrlCfg;

typedef struct CanIfHthCfg {
	//Reference to controller Id to which the HTH belongs to
	const CanIfCtrlCfg *canIfHthCanCtrlIdRef;

	//The parameter refers to a particular HTH object in the CanDrv configuration
	const CanHardwareObject *canIfHthIdSymRef;

} CanIfHthCfg;

typedef struct CanIfBufferCfg {
	//number of CanIf Tx L-PDUs which can be buffered in one Txbuffer */
	uint8 canIfBufferSize;
	// Reference to HTH,that defines the hardware object
	const CanIfHthCfg *canIfBufferHthRef;
} CanIfBufferCfg;

typedef struct CanIfHrhRangeCfg {
	CanIfHrhRangeRxPduRangeCanIdType canIfHrhRangeRxPduRangeCanIdType;
	//BASEID + RANGEMASK = masked ID range in which all CAN Ids shall pass the software filtering
	uint32 canIfHrhRangeBaseId;
	uint32 canIfHrhRangeMask;
	//upper and lower bound of canIDs range
	uint32 canIfHrhRangeRxPduLowerCanId;
	uint32 canIfHrhRangeRxPduUpperCanId;
} CanIfHrhRangeCfg;

typedef struct CanIfHrhCfg {
	//Reference to controller Id to which the HRH belongs to.
	const CanIfCtrlCfg *canIfHrhCanCtrlIdRef;

	//The parameter refers to a particular HRH object in the CanDrv configuration
	const CanHardwareObject *canIfHrhIdSymRef;

	//True: Software filtering is enabled False: Software filtering is enabled
	const bool canIfHrhSoftwareFilter;

	/*Defines the parameters required for configurating multiple CANID ranges for a given same HRH.*/
	const CanIfHrhRangeCfg *canIfHrhRangeCfg;

} CanIfHrhCfg;

/*This container contains the configuration (parameters) of each receive CAN L-PDU*/
typedef struct CanIfRxPduCfg {
	//CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
	uint32 canIfRxPduCanId;

	//Identifier mask which denotes relevant bits in the CAN Identifier. 
	//This parameter defines a CAN Identifier range in an alternative way to CanIfRxPduCanIdRange.
	uint32 canIfRxPduCanIdMask;

	//CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CANL-PDU reception.
	CanIfPduCanIdType canIfRxPduCanIdType;

	//Data length of the received CAN L-PDUs used by the CAN Interface.
	uint8 canIfRxPduDlc;

	//The HRH to which Rx L-PDU belongs to, is referred through this parameter.
	CanIfHrhCfg *canIfRxPduHrhIdRef;

	// ECU wide unique, symbolic handle for receive CAN L-SDU
	const uint32 CanIfRxPduId;

	// Enables and disables the Rx buffering for reading of received L-SDU data.
	bool canIfRxPduReadData;

	// Enables and disables receive indication for each receive CAN L-SDU for reading its notification status.
	bool canIfRxPduReadNotifyStatus;

	// Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
	void *canIfRxPduRef;

	//This parameter defines the name of the <User_RxIndication>
	CanIfRxPduUserRxIndicationNameType canIfRxPduUserRxIndicationName;

	/*This parameter defines the upper layer (UL) module to which the indication of the successfully received CANRXPDUID has to be routed via <User_RxIndication>.*/
	CanIfRxPduUserRxIndicationULType canIfRxPduUserRxIndicationUL;

	// /** This parameter defines the name of the <User_INF_GetPduHandleId> */
	// CanIf_INF_GetPduHandleIdNameType CanIf_INF_GetPduHandleIdName;

	//Optional container that allows to map a range of CAN Ids to one PduId.
	const CanIfRxPduCanIdRange *canIfRxPduCanIdRange;

} CanIfRxPduCfg;

typedef struct CanIfInitHohCfg {
	//This container contains configuration parameters for each hardware receive object (HRH).
	CanIfHrhCfg *canIfHrhCfg;
	//This container contains parameters related to each HTH.
	CanIfHthCfg *canIfHthCfg;
} CanIfInitHohCfg;

typedef struct CanIfTxPduCfg {
	//Configurable reference to a CanIf buffer configuration.
	const CanIfBufferCfg *canIfTxPduBufferRef;
	//CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission
	uint16 canIfTxPduCanId;
	//Identifier mask which denotes relevant bits in the CAN Identifier.
	uint32 canIfTxPduCanIdMask;
	//Type of CAN Identifier of the transmit CAN L-PDU used by the CAN Driver module for CAN L-PDU transmission.
	CanIfPduCanIdType canIfTxPduCanIdType;
	//ECU wide unique,
	const uint32 canIfTxPduId;
	//If CanIfPublicPnFilterSupport is enabled,
	bool canIfTxPduPnFilterPdu;
	//Enables and disables transmit confirmation for each transmit CAN L-SDU for reading its notification status.
	bool canIfTxPduReadNotifyStatus;
	//Reference to the "global" Pdu structure
	void *canIfTxPduRef;
	/** Determines if or if not CanIf shall use the trigger transmit API for this PDU */
	bool canIfTxPduTriggerTransmit;
	/** Defines the type of each transmit CAN L-PDU */
	CanIfTxPduType canIfTxPduType;
	/** This parameter defines the name of the <User_TriggerTransmit> */
	const CanIfTxPduUserTriggerTransmitName canIfTxPduUserTriggerTransmitName;
	/** This parameter defines the name of the <User_TxConfirmation> */
	const CanIfTxPduUserTxConfirmationName canIfTxPduUserTxConfirmationName;
	// confirmation of the successfully transmitted CANTXPDUID has to be routed via the <User_TxConfirmation>
	const CanIfTxPduUserTxConfirmationUL canIfTxPduUserTxConfirmationUL;
} CanIfTxPduCfg;

typedef struct CanIfTrcvCfg {
	/*This parameter references to the logical handle of the underlying CAN transceiver from the CAN transceiver driver module to be served by the CAN Interface module.*/
	void *CanIfTrcvCanTrcvRef;
	/*This parameter abstracts from the CAN Transceiver Driver specific
	parameter Transceiver. Each transceiver of all connected CAN
	Transceiver Driver modules shall be assigned to one specific
	TransceiverId of the CanIf.*/
	uint8 CanIfTrcvId;
	/*This parameter defines if a respective transceiver of the referenced CAN Transceiver Driver modules is queriable for wake up events.*/
	bool CanIfTrcvWakeupSupport;
} CanIfTrcvCfg;

/*This container contains the configuration (parameters) of all addressed
CAN transceivers by each underlying CAN Transceiver Driver module.
For each CAN transceiver Driver a seperate instance of this container
shall be provided.
 */
typedef struct CanIfTrcvDrvCfg {
	const CanIfTrcvCfg canIfTrcvCfg;

} CanIfTrcvDrvCfg;

/*
	Configuration parameters for all the underlying CAN Driver modules are aggregated under this container. For each CAN Driver module a
	separate instance of this container has to be provided.
 */
typedef struct CanIfCtrlDrvCfg {
	//reference to init HOH Configuration
	CanIfInitHohCfg canIfCtrlDrvInitHohConfigRef;
	//CAN Interface Driver Reference. This reference can be used to get any information (Ex. Driver Name, Vendor ID) from the CAN driver.
	const void *canIfCtrlDrvNameRef;
	/*This container contains the configuration (parameters) of an adressed CAN controller by an underlying CAN
	Driver module. This container is configurable per CAN controller.*/
	CanIfCtrlCfg canIfCtrlCfg;
} CanIfCtrlDrvCfg;

/*
	Callback functions provided by upper layer modules of the CanIf. The callback functions defined in this container are common to all
	configured CAN Driver / CAN Transceiver Driver modules.
 */
typedef struct CanIfDispatchCfg {
	//  defines the name of <User_ClearTrcvWufFlagIndication>
	CanIfDispatchUserCheckTrcvWakeFlagIndicationName canIfDispatchUserCheckTrcvWakeFlagIndicationName;
	//  defines the upper layer module to which the CheckTrcvWakeFlagIndication from the Driver modules have to be routed
	CanIfDispatchUserCheckTrcvWakeFlagIndicationUL canIfDispatchUserCheckTrcvWakeFlagIndicationUL;
	//  defines the name of <User_ClearTrcvWufFlagIndication> */
	CanIfDispatchUserClearTrcvWufFlagIndicationName canIfDispatchUserClearTrcvWufFlagIndicationName;
	//  defines the upper layer module to which the ClearTrcvWufFlagIndication from the Driver modules have to be routed
	CanIfDispatchUserClearTrcvWufFlagIndicationUL canIfDispatchUserClearTrcvWufFlagIndicationUL;
	/** defines the name of <User_ConfirmPnAvailability> */
	CanIfDispatchUserConfirmPnAvailabilityName canIfDispatchUserConfirmPnAvailabilityName;
	// defines the upper layer module to which the ConfirmPnAvailability notification from the Driver modules have to be routed
	CanIfDispatchUserConfirmPnAvailabilityUL canIfDispatchUserConfirmPnAvailabilityUL;
	/** defines the name of <User_ControllerBusOff> */
	CanIfDispatchUserCtrlBusOffName canIfDispatchUserCtrlBusOffName;
	/** defines the upper layer (UL) module to which the notifications of all ControllerBusOff events from the CAN Driver modules have to be routed */
	CanIfDispatchUserCtrlBusOffULType canIfDispatchUserCtrlBusOffUL;
	/** defines the name of <User_ControllerModeIndication> */
	//    CanIfDispatchUserCtrlModeIndicationName canIfDispatchUserCtrlModeIndicationName;
	/** defines the upper layer (UL) module to which the notifications of all ControllerTransition events from the CAN Driver modules have to be routed */
	CanIfDispatchUserCtrlModeIndicationUL canIfDispatchUserCtrlModeIndicationUL;
	/** defines the name of <User_TrcvModeIndication> */
	//    CanIfDispatchUserTrcvModeIndicationName canIfDispatchUserTrcvModeIndicationName;
	/** defines the upper layer (UL) module to which the notifications of all TransceiverTransition events from the CAN Transceiver Driver modules have to be routed */
	CanIfDispatchUserTrcvModeIndicationUL canIfDispatchUserTrcvModeIndicationUL;
	/** defines the name of <User_ValidateWakeupEvent> */
	//    CanIfDispatchUserValidateWakeupEventName canIfDispatchUserValidateWakeupEventName;
	/** defines the upper layer (UL) module to which the notifications about positive former requested wake up sources have to be routed */
	CanIfDispatchUserValidateWakeupEventULType canIfDispatchUserValidateWakeupEventUL;
} CanIfDispatchCfg;



//This container contains the init parameters of the CAN Interface.

typedef struct CanIfInitCfg {
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
	const CanIfBufferCfg *canIfBufferCfg;
	//This container contains the references to the configuration setup of each underlying CAN Driver.
	const CanIfInitHohCfg *canIfInitHohCfg;
	//This container contains the configuration (parameters) of each receive CAN L-PDU.
	CanIfRxPduCfg *canIfRxPduCfg;
	//This container contains the configuration (parameters) of a transmit CAN L-PDU
	CanIfTxPduCfg *canIfTxPduCfg;
} CanIfInitCfg;



//This container contains the private configuration (parameters) of the CAN Interface.

typedef struct CanIfPrivateCfg {
	//TRUE:  Minimum buffer element length is fixed to 8 Bytes.
	//FALSE: Buffer element length depends on the size of the referencing PDUs.
	bool CanIfFixedBuffer;
	//TRUE: Enabled
	//False : Disabled
	bool CanIfPrivateDlcCheck;
	//Selects the desired software filter mechanism for reception only.
	CanIfPrivateSoftwareFilterType canIfPrivateSoftwareFilterType;
} CanIfPrivateCfg;




//This container contains the public configuration (parameters) of the CAN Interface.

typedef struct CanIfPublicCfg {
	//Enable support for dynamic ID handling using L-SDU MetaData.
	bool canIfMetaDataSupport;

	//Enable or disable upper layer transmit cancel support
	bool canIfPublicCancelTransmitSupport;

	//Defines header files for callback functions which shall be included in case of CDDs
	uint8 *canIfPublicCddHeaderFile;

	//Switches the Default Error Tracer (Det) detection and notification ON or OFF
	bool canIfPublicDevErrorDetect;

	/*  This parameter is used to configure the Can_HwHandleType. The
		Can_HwHandleType represents the hardware object handles of a CAN
		hardware unit
	 */
	CanIfPublicHandleTypeEnum canIfPublicHandleTypeEnum;

	//Selects support of Pretended Network features in CanIf. True: Enabled False: Disabled
	bool canIfPublicIcomSupport;

	//Selects support for multiple CAN Drivers.
	bool canIfPublicMultipleDrvSupport;

	//Selects support of Partial Network features in CanIf.
	bool canIfPublicPnSupport;

	//Enables-Disables the API CanIf_ReadRxPduData() for reading received L-SDU data.
	bool canIfPublicReadRxPduDataApi;

	//Enables and disables the API for reading the notification status of receive L-PDUs.
	bool canIfPublicReadRxPduNotifyStatusApi;

	//Enables and disables the API for reading the notification status of transmit L-PDUs.
	bool canIfPublicReadTxPduNotifyStatusApi;

	// Enables and diables the API for reconfiguation of the CAN Identifier for each transmit L-PDU
	bool canIfPublicSetDynamicTxIdApi;

	// Enables and diables the buffering of transmit L-Pdu within the CAN Interface Module
	bool canIfPublicTxBuffering;

	// Configuration parameter to enable/disable the API to poll for Tx Confirmation state
	bool canIfPublicTxConfirmPollingSupport;

	// Enables and disables the API for reading the version information about the CAN Interface.
	bool canIfPublicVersionInfoApi;

	/*
		If enabled, only NM messages shall validate a detected wake-up event in CanIf.
		If disabled, all received messages corresponding to a configured Rx PDU shall validate such a wake-up event.
	 */
	bool canIfPublicWakeupCheckValidByNM;

	//Selects support for wake up validation
	bool canIfPublicWakeupCheckValidSupport;

	// If this parameter is set to true the CanIf_SetBaudrate API shall be supported.
	bool canIfSetBaudrateApi;

	// Enables the CanIf_TriggerTransmit API at Pre-Compile-Time.
	bool canIfTriggerTransmitSupport;

	// Determines wether TxOffLineActive feature is supported by CanIf.
	bool canIfTxOfflineActiveSupport;

	/*
		Enables the CanIf_CheckWakeup API at Pre-Compile-Time.
		this parameter defines if there shall be support for wake-up.
	 */
	bool canIfWakeupSupport;

} CanIfPublicCfg;


//THE BIG CONTAINER OF ALL CANIF TYPES

typedef struct CanIf_ConfigType {
	//This container contains the private configuration (parameters) of the CAN Interface.
	const CanIfPrivateCfg *canIfPrivateCfg;

	//This container contains the public configuration (parameters) of the CAN Interface.
	const CanIfPublicCfg *canIfPublicCfg;

	//This container contains the init parameters of the CAN Interface.
	const CanIfInitCfg *canIfInitCfg;

	/*
		Configuration parameters for all the underlying CAN
		Driver modules are aggregated under this container.
		For each CAN Driver module a seperate instance of
		this container has to be provided.
	 */
	const CanIfCtrlDrvCfg *canIfCtrlDrvCfg;

	/*
		Callback functions provided by upper layer modules of the CanIf.
		The callback functions defined in this container are common to
		all configured CAN Driver / CAN Transceiver Driver modules.
	 */
	const CanIfDispatchCfg *canIfDispatchCfg;

	/** List of CAN transceivers
		This container contains the configuration (parameters) of all addressed CAN transceivers
		by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver
		a seperate instance of this container shall be provided.
	 */
	const CanIfTrcvDrvCfg *canIfTrcvDrvCfg;

} CanIf_ConfigType;