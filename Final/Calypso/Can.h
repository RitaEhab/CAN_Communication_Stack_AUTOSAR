#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"
#include "Can_Cfg.h"
#include "Can_PBcfg.h"
#include "Micro_Registers.h"


#define CAN_VENDOR_ID    			(31U)
#define CAN_MODULE_ID    			(80U)
#define CAN_INSTANCE_ID  			(0U)

/*	Module Version 1.0.0	*/
#define CAN_SW_MAJOR_VERSION           (1U)
#define CAN_SW_MINOR_VERSION           (0U)
#define CAN_SW_PATCH_VERSION           (0U)


/******************************************************************************
 *                      	API Service ID 	                                  *
 ******************************************************************************/

#define CAN_INIT_SID						(uint8)0x00
#define CAN_GET_VERSION_INFO_SID			(uint8)0x07
#define CAN_WRITE_SID						(uint8)0x06

/*******************************************************************************
 *                      	DET ERRORS                                         *
 *******************************************************************************/

#define CAN_E_PARAM_POINTER					(uint8)0x01
#define CAN_E_PARAM_HANDLE					(uint8)0x02
#define CAN_E_PARAM_DATA_LENGTH				(uint8)0x03
#define CAN_E_PARAM_CONTROLLER				(uint8)0x04

#define CAN_E_UNINIT						(uint8)0x05
#define CAN_E_TRANSITION					(uint8)0x06
#define CAN_E_PARAM_BAUDRATE				(uint8)0x07
#define CAN_E_INIT_FAILED					(uint8)0x09

/*******************************************************************************
 *                      	Function Prototypes                                *
 *******************************************************************************/

void Can_Init( const Can_ConfigType* Config );

#if (CAN_VERSION_INFO_API == STD_ON)
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif
Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo );


#endif // CAN_H_INCLUDED
