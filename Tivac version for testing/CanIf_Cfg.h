#ifndef CANIF_CFG_H_INCLUDED
#define CANIF_CFG_H_INCLUDED

/* -------------------------------------------------------------------------- */
/*                           Macros & Typedefs                                */
/* -------------------------------------------------------------------------- */
/** CANIF_INF_RUNTIME_PDU_CONFIGURATION
    STD_OFF ->  Pre-compile time configuration
    STD_ON  ->  Post build time configuration
    m4 mwgodeen
*/
#define CAN_IF_ID 2

#define CANIF_INF_RUNTIME_PDU_CONFIGURATION      STD_OFF
#define CANIF_INF_CAN_TRCV_SUPPORT               STD_ON

/** service CanIf_CancelTransmit() shall be pre-compile time
    configurable On/Off
*/
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT     STD_ON

/** CanIf_ReadRxPduData(): This API can
    be enabled or disabled at pre-compile time
*/
#define CANIF_PUBLIC_READRXPDU_DATA_API          STD_OFF
#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API STD_OFF
#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API STD_OFF

#define CANIF_INF_WAKEUP_SUPPORT                         STD_ON
#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT     STD_ON
#define CANIF_INF_PUBLIC_TX_CONFIRMATION_POLLING_SUPPORT STD_ON
#define CANIF_PUBLIC_PN_SUPPORT                  STD_ON
#define CANIF_SET_BAUDRATE_API                   STD_ON
#define CANIF_PUBLIC_ICOM_SUPPORT                STD_ON

/** Enables and disables the API for reading the notification
    status of transmit L-PDUs.
*/
#define CANIF_READTXPDU_NOTIFY_STATUS_API        STD_OFF
#define CANIF_PUBLIC_SETDYNAMICTXID_API          STD_OFF

#define CANIF_INF_PRIVATE_DATA_LENGTH_CHECK      STD_ON

#define CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT      STD_ON

/** Max number of can driver controllers */
#define CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT         1
#define CANIF_INF_CAN_DRIVER_0_CONTROLER_0           0

/** Max number of can tranceiver  driver tranceivers  */
#define CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT  1
#define CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_0    0

//#define CANIF_INF_USE_CAN_NM                    STD_OFF
//#define CANIF_INF_USE_CAN_TP                    STD_OFF
//#define CANIF_INF_USE_CAN_TSYN                  STD_OFF
//#define CANIF_INF_USE_CDD                       STD_OFF
//#define CANIF_INF_USE_J1939NM                   STD_OFF
//#define CANIF_INF_USE_J1939TP                   STD_OFF
//#define CANIF_INF_USE_PDUR                      STD_OFF
//#define CANIF_INF_USE_XCP                       STD_OFF
#include "CanIf_Types.h"
#define CANIF_INF_RX_PDU_0_CAN_ID   1
#define CANIF_INF_TX_PDU_0_CAN_ID   0

#define CANIF_PDU_ID_CAN_RX_PDUR 1
#define CANIF_PDU_ID_CANIF_TX_CAN 0


/* -------------------------------------------------------------------------- */
/*                       Structures and Enumerations                          */
/* -------------------------------------------------------------------------- */
/*typedef enum {
	CANIF_INF_RX_PDU_0 = 0,   ///PduR
	CANIF_INF_RX_CNT = 1
}CanIf_INF_Rx_Pdus;
typedef enum {
	CANIF_INF_TX_PDU_0 = 0,   ///PduR
	CANIF_INF_TX_CNT = 1
}CanIf_Rx_Pdus;*/

/* -------------------------------------------------------------------------- */
/*                      Global variables  Declarations	                      */
/* -------------------------------------------------------------------------- */
extern const CanIf_ConfigType canIf_Config;
#endif // CANIF_CFG_H_INCLUDED