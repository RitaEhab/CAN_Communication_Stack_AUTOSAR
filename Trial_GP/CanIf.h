/*
 * CanIf.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CANIF_H_
#define CANIF_H_

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

/******************************************************************************
 *                     	 API Service ID 	                                  *
 ******************************************************************************/

#define CAN_INIT_SID							(uint8)0x01
#define CANIF_DEINIT_SID                        (uint8)0x02
#define CANIF_SET_CONTROLLER_MODE_SID   		(uint8)0x03
#define CANIF_GET_CONTROLLER_MODE_SID   		(uint8)0x04
#define CANIF_Get_CONTROLLER_ERRORSTATE_SID   	(uint8)0x4b
#define CANIF_TRANSMIT_SID                      (uint8)0x49
#define CANIF_CANCEL_TRANSMIT_SID               (uint8)0x4a
#define CANIF_RXINDICATION_SID 					(uint8)0x14
#define CANIF_TXCONFIRMATION_SID          		(uint8)0x13

/*******************************************************************************
 *                      	DET ERRORS                                         *
 *******************************************************************************/

#define CANIF_E_PARAM_CANID 			10
#define CANIF_E_PARAM_HOH    			12
#define CANIF_E_PARAM_LPDU    			13
#define CANIF_E_PARAM_CONTROLLERID      15
#define CANIF_E_PARAM_WAKEUPSOURCE 		16
#define CANIF_E_PARAM_TRCV  			17
#define CANIF_E_PARAM_TRCVMODE  		18
#define CANIF_E_PARAM_TRCVWAKEUPMODE  	19
#define CANIF_E_PARAM_CTRLMODE  		21
#define CANIF_E_PARAM_PDU_MODE  		22
#define CANIF_E_PARAM_POINTER 			20
#define CANIF_E_UNINIT 					30
#define CANIF_E_INVALID_TXPDUID 		50
#define CANIF_E_INVALID_RXPDUID			60
#define CANIF_E_INIT_FAILED   			80
#define CANIF_E_INVALID_DATA_LENGTH 	61
#define CANIF_E_DATA_LENGTH_MISMATCH   	62
#define CANIF_E_STOPPED 				70
#define CANIF_E_TXPDU_LENGTH_EXCEEDED  	90

/*******************************************************************************
 *                      	Function Prototypes                                *
 *******************************************************************************/

void CanIf_Init(const CanIf_ConfigType* ConfigPtr);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);


#endif /* CANIF_H_ */
