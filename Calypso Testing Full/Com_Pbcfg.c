#include "Com_Types.h"


PduInfoType pduInfoType={
	.SduLength = 8
};

ComSignal comSignal = {
	.ComHandleId = 0
};


ComIPdu com_IPdu [] = {
	{
	    /* RECEIVE COM PDU */
	.comIPduDirection = COM_RECEIVE,
	.ComIPduHandleId = 10,
	.comIPduSignalProcessing= IMMEDIATE,
	.comIPduType = NORMAL,
	.ComPduIdRef= &pduInfoType,
	.comIPduSignalRef = &comSignal
	},
	{
	    /* TRANSMIT COM PDU */
	.comIPduDirection = COM_SEND,
	.ComIPduHandleId = 20,
	.comIPduSignalProcessing= IMMEDIATE,
	.comIPduType = NORMAL,
	.ComPduIdRef= &pduInfoType,
	.comIPduSignalRef = &comSignal
	}
};

ComConfig com_Config = {
	.ComMaxIPduCnt = 5,
	.comIPdu = &com_IPdu
};

Com_ConfigType com_ConfigType = {
	.comConfig = &com_Config
};
