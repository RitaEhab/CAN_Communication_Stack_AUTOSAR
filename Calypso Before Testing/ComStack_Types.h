/*
 * ComStack_Types.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Rita
 */

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

#include "Std_Types.h"

/* MOVED TO CAN_GENERALTYPES.H */
/* Maximum number of PDUs (Protocol data unit) used within one software module */
//typedef uint8 PduIdType;

/* Maximum payload size of a frame of the underlying communication system */
typedef uint8 PduLengthType;

/* stores basic info about PDU  */
typedef struct{
	uint8* SduDataPtr;
	uint8* MetaDataPtr;
	PduLengthType SduLength;
} PduInfoType;

/* stores the result of a buffer request */
typedef enum BufReq_ReturnType {
	BUFREQ_OK,
	BUFREQ_E_NOT_OK,
	BUFREQ_E_BUSY,
	BUFREQ_E_OVFL
}BufReq_ReturnType;


/* stores identifier of a communication channel */
typedef uint8 NetworkHandleType;


#endif /* COMSTACK_TYPES_H_ */
