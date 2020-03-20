/*
 * CanIf_Cfg.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_


#define CanIfFixedBuffer 					STD_ON   // we choose fixed size of buffer element 8 bytes
#define CanIfPrivateDataLengthCheck 		STD_ON
#define CANIF_PUBLIC_DEV_ERROR_DETECT		STD_ON
#define CanIfMetaDataSupport				STD_OFF  // Disable support for dynamic ID handling using L-SDU MetaData
#define	CanIfPublicCancelTransmitSupport 	STD_ON
#define CanIfPublicIcomSupport				STD_OFF  // Disable support of Pretended Network features in CanIf
#define CanIfPublicMultipleDrvSupport		STD_OFF  // Disable support for multiple CAN Drivers
#define CanIfPublicPnSupport				STD_OFF  // Disable support of Partial Network features in CanIf
#define CanIfPublicReadRxPduDataApi			STD_OFF  // Didn't implement the function at all
#define CanIfPublicReadRxPduNotifyStatusApi	STD_OFF
#define CanIfPublicReadTxPduNotifyStatusApi	STD_OFF
#define CanIfPublicSetDynamicTxIdApi		STD_OFF  // Disables the API for reconfiguration of the CAN Identifier
													 //	for each Transmit L-PDU
#define CanIfPublicTxBuffering				STD_OFF  // Disables the buffering of transmit L-PDUs
#define CanIfPublicTxConfirmPollingSupport	STD_OFF  // Disable the API to poll for Tx
													 //	Confirmation state
#define CanIfPublicWakeupCheckValidByNM
#define CanIfTxOfflineActiveSupport			STD_OFF

							/* CanIfTxPduCfg CONTAINER */

#define CanIfTxPduUserTriggerTransmitName	FUNCTION_MA
#define CanIfTxPduUserTxConfirmationName	FUNCTION_MA
/*  defines the upper layer (UL) module to which the confirmation of the successfully
 * transmitted CANTXPDUID has to be routed via the <User_TxConfirmation> */
#define CanIfTxPduUserTxConfirmationUL		PDUR


							/* CanIfRxPduCfg CONTAINER */

#define CanIfRxPduUserRxIndicationName		FUNCTION_MA
#define CanIfRxPduUserRxIndicationUL		PDUR


							/* CanIfCtrlCfg CONTAINER */

#define CanIfCtrlId							(0U)		// Each controller shall be assigned to one specific
														//	ControllerId of the CanIf
#define CanIfCtrlWakeupSupport				STD_OFF		// Disable wake up events


#endif /* CANIF_CFG_H_ */
