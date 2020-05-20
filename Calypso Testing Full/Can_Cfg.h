#ifndef CAN_CFG_H_INCLUDED
#define CAN_CFG_H_INCLUDED

/*******************************************************************************
 *                      		 CanGeneral                                    *
 *******************************************************************************/

#define CAN_DEV_ERROR_DETECT 			STD_OFF
#define CanIndex 						(uint8)0x00		// Specifies the InstanceId of this module instance
#define CanLPduReceiveCalloutFunction	CanIf_RxIndication		// callout function after reception of L-PDU
#define CAN_VERSION_INFO_API			STD_ON


#endif // CAN_CFG_H_INCLUDED
