/*
 * Com_Pbcfg.c
 *
 *  Created on: May 1, 2020
 *      Author: Rita
 */

#include "Com_Types.h"


PduInfoType pduInfoType={
	.SduLength = 8
};

ComSignal comSignal = {
	.ComHandleId = 17
};

/* RECEIVE COM PDU */
ComIPdu com_IPdu = {
	.comIPduDirection = RECEIVE,
	.ComIPduHandleId = 10,
	.comIPduSignalProcessing= IMMEDIATE,
	.comIPduType = NORMAL,
	.ComPduIdRef= &pduInfoType
	.ComIPduSignalRef = &comSignal
};

ComConfig com_Config = {
	.ComMaxIPduCnt = 5,
	.comIPdu = &com_IPdu
};

Com_ConfigType com_ConfigType = {
	.comConfig = &com_Config
};

/* ARRAY OF STRUCT FOR MAPPING IDS FROM COM AND PDUR
 * INDEX OF ARRAY = PDUR_PDU_ID
 * MEMBER OF STRUCT = COM_PDU_ID
 * */
PDU_COM_MAP PDU_PDUR_COM[] = {
	{
		//	PDUR_ID = 0
	},
	{
		//	PDUR_ID = 1
	},
	{
		//	PDUR_ID = 2
	},
	{
		//	PDUR_ID = 3
		.COM_PDU_ID = 10
	},
	{
		//	PDUR_ID = 4
		.COM_PDU_ID = 20
	}
};
