#ifndef CANIF_CFG_H_INCLUDED
#define CANIF_CFG_H_INCLUDED


									/* CanIfPrivateCfg CONTAINER */

#define CanIfFixedBuffer 					STD_ON	 // Fixed size of buffer element 8 bytes
#define CanIfPrivateDataLengthCheck 		STD_ON	 // Data Length Check is supported
#define CanIfPrivateSoftwareFilterType		BINARY	 // Won't be used when using FULL CAN
#define CanIfSupportTTCAN					STD_OFF `// TTCAN is not supported


									/* CanIfPublicCfg CONTAINER */

#define CANIF_PUBLIC_DEV_ERROR_DETECT		STD_ON	 // Detection and notification is enabled
#define CanIfMetaDataSupport				STD_OFF  // Disable support for dynamic ID handling using L-SDU MetaData
#define	CanIfPublicCancelTransmitSupport 	STD_OFF	 // disable dummy API for upper layer modules which allows to
													 //	request the cancellation of an I-PDU

#define CanIfPublicHandleTypeEnum			UINT8	 // CAN hardware units equal to or less than 255 HW objects
#define CanIfPublicIcomSupport				STD_OFF  // Disable support of Pretended Network features in CanIf
#define CanIfPublicMultipleDrvSupport		STD_OFF  // Disable support for multiple CAN Drivers
#define CanIfPublicPnSupport				STD_OFF  // Disable support of Partial Network features in CanIf
#define CanIfPublicReadRxPduDataApi			STD_OFF  // Disables the API CanIf_ReadRxPduData()
#define CanIfPublicReadRxPduNotifyStatusApi	STD_OFF	 // Disables the API for reading the notification status of
													 //	receive L-PDUs.

#define CanIfPublicReadTxPduNotifyStatusApi	STD_OFF	 // Disables the API for reading the notification status of
													 //	transmit L-PDUs.

#define CanIfPublicSetDynamicTxIdApi		STD_OFF  // Disables the API for reconfiguration of the CAN Identifier
													 //	for each Transmit L-PDU

#define CanIfPublicTxBuffering				STD_OFF  // Disables the buffering of transmit L-PDUs
#define CanIfPublicTxConfirmPollingSupport	STD_OFF  // Disable the API to poll for Tx
													 //	Confirmation state

#define CanIfPublicWakeupCheckValidSupport	STD_OFF	 // Disables support for wake up validation
#define CanIfTriggerTransmitSupport			STD_OFF	 // Disables the CanIf_TriggerTransmit API
#define CanIfTxOfflineActiveSupport			STD_OFF	 // Disables TxOffLineActive feature

#define CanIfVersionInfoApi					STD_OFF	 // disables the API for reading the version information about
													 //	the CAN Interface

#define CanIfWakeupSupport					STD_OFF	 // Disables the CanIf_CheckWakeup API


							/* CanIfTxPduCfg CONTAINER */


#define CanIfTxPduUserTxConfirmationName	PduR_CanIfTxConfirmation
/*  defines the upper layer (UL) module to which the confirmation of the successfully
 * transmitted CANTXPDUID has to be routed via the <User_TxConfirmation> */
#define CanIfTxPduUserTxConfirmationUL		PDUR


							/* CanIfRxPduCfg CONTAINER */

#define CanIfRxPduUserRxIndicationName		PduR_CanIfRxIndication
#define CanIfRxPduUserRxIndicationUL		PDUR

#endif // CANIF_CFG_H_INCLUDED
