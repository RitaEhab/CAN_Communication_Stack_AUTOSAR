#include <stddef.h>
#include "PduR.h"
#include "CanIf.h"
//#include "Can.h"


const CanIfRxPduCanIdRange canIfRxPduCanIdRange = {
    .CanIfRxPduCanIdRangeLowerCanId = 0,
    .CanIfRxPduCanIdRangeUpperCanId = 24,
};
const CanIfCtrlCfg canIfHrhCanCtrlIdRef = {
    .canIfCtrlId = 130,
    .canIfCtrlWakeupSupport = false,
};
CanHardwareObject canIfHrhIdSymRef = {
	.canObjectId = 1,
	.canHandleType = BASIC
};
CanIfHrhCfg canIfHrhCfg = {
    //software filter feature
    .canIfHrhSoftwareFilter = false,

    // HRH HW object (to check with tair)
     .canIfHrhIdSymRef = &canIfHrhIdSymRef,

    // CanIf Controller Configurations
    .canIfHrhCanCtrlIdRef = &canIfHrhCanCtrlIdRef,
    //HRH range for multiple CANID ranges
    .canIfHrhRangeCfg = NULL,
};
CanIfRxPduCfg canIfRxPduCfg[] = {
    {
        //CanId that CanIf use
		.CanIfRxPduId = CANIF_PDU_ID_CAN_RX_PDUR,
				//??
        .canIfRxPduCanId = CANIF_INF_RX_PDU_0_CAN_ID,
        // mask range
        .canIfRxPduCanIdMask = 0x7FF,
        // CanIfPduCanIdType used by the Can Driver
        .canIfRxPduCanIdType = STANDARD_CAN,
        // data length code
        .canIfRxPduDlc = 1,
        // buffering feature 
        .canIfRxPduReadData = false,
        // notification feature
        .canIfRxPduReadNotifyStatus = false,
        
        // user_RXIndication to be defined by wagih (RX Indication of PduR)
        .canIfRxPduUserRxIndicationName = PduR_CanIfRxIndication,
                
                
        .canIfRxPduCanIdRange = &canIfRxPduCanIdRange,
        //HRH configurations
        .canIfRxPduHrhIdRef = &canIfHrhCfg,
    }
};
const CanIfCtrlCfg canIfHthCanCtrlIdRef = {
    .canIfCtrlId = 150,
    .canIfCtrlWakeupSupport = false,
};

CanHardwareObject canIfHthIdSymRef = {
	.canObjectId = 0,
	.canHandleType = BASIC
};

CanIfHthCfg canIfHthRef = {
    .canIfHthCanCtrlIdRef = &canIfHthCanCtrlIdRef,
    //check with tair the CAN hardware objects
    .canIfHthIdSymRef = &canIfHthIdSymRef,

};
const CanIfBufferCfg canIfTxPduBufferRef = {
    .canIfBufferSize = sizeof (fp64_t)*1,
    .canIfBufferHthRef = &canIfHthRef,
};
CanIfTxPduCfg canIfTxPduCfg[] = {
    {
        //pdu canID used by can Driver in transmission (check m3 CanDriver Configuration)
        .canIfTxPduCanId = CANIF_INF_TX_PDU_0_CAN_ID,
        // wide unique ID
        .canIfTxPduId = CANIF_PDU_ID_CANIF_TX_CAN,
        //in case a mask will be used set it to another value
        .canIfTxPduCanIdMask = 0x7FF,
        // pduCanIdType
        .canIfTxPduType = STATIC,
        //CanIfPduCanIdType
        .canIfTxPduCanIdType = STANDARD_CAN,
        // will trigger transmit or not
        .canIfTxPduTriggerTransmit = false,
        // support PN filtering
        .canIfTxPduPnFilterPdu = false,
        //CanIfTxPduUserTxConfirmationUL
        .canIfTxPduUserTxConfirmationUL = PDUR,
        
        //user TX Confirmation method (el method ele 3nd PduR ele CANIf Hae3mlaha call fl tx confirmation) 
        //.canIfTxPduUserTxConfirmationName = PduR_CanIfTxConfirmation,

        .canIfTxPduBufferRef = &canIfTxPduBufferRef,

		.canIfTxPduRef = &Pdus[1],
    },

};
const CanIfInitHohCfg canIfInitHohCfg = {
    .canIfHrhCfg = &canIfHrhCfg,
    .canIfHthCfg = &canIfHthRef,
};
const CanIfInitCfg canIfInitCfg = {

    .canIfInitCfgSet = 0,
    //bufferSize (don't know whether we support buffering or not)
    .canIfMaxBufferSize = sizeof (fp64_t)*4,
    //one receive PDU
    .canIfMaxRxPduCfg = 1,
    //one send PDU
    .canIfMaxTxPduCfg = 1,
    //Tx Pdu Cfg
    .canIfTxPduCfg = &canIfTxPduCfg[0],
    //RX pdy Cfg
    .canIfRxPduCfg = &canIfRxPduCfg[0],
    //HOH cfgs
    .canIfInitHohCfg = &canIfInitHohCfg
};

const CanIf_ConfigType canIf_Config = {
    .canIfInitCfg = &canIfInitCfg,
};