#include "Can.h"
#include "Common_Macros.h"
#include "CanIf_Cbk.h"
#include "tm4c123gh6pm.h"

STATIC const Can_ConfigType* Can_ConfigStructPtr = NULL_PTR;
STATIC Can_StateType CAN_STATE = CAN_UNINIT;
STATIC Can_ControllerStateType CAN_CONTROLLER_STATE = CAN_CS_UNINIT;
STATIC uint8 mutex =0;

/*
	CAN0 Pins:
	CAN0Rx PB4
	CAN0Tx PB5
*/

void CAN_REG_INIT ()
{
	SYSCTL_RCGC0_R = 0x01000000;		// Enable Can0 clock gating
	SYSCTL_RCGC2_R = 0x00000002;		// Enable PORTB clock gating
	GPIO_PORTB_AFSEL_R = 0x00000030;	// Enable pin alternate functions for PB4, PB5
	GPIO_PORTB_PCTL_R = 0x00880000;		// Configure CAN0 for pins PB4, PB5

	CAN0_CTL_R = 0x00000041;		// Set INIT, CCE bit
	CAN0_BIT_R = 0;
	CAN0_BIT_R = 	Can_ConfigStructPtr->canController->canControllerBaudrateConfig->CanControllerSeg2 << 12 |
			Can_ConfigStructPtr->canController->canControllerBaudrateConfig->CanControllerSeg1 << 8  |
			Can_ConfigStructPtr->canController->canControllerBaudrateConfig->CanControllerSyncJumpWidth << 6  |
			Can_ConfigStructPtr->canController->canControllerBaudrateConfig->CanControllerPropSeg;
	CLEAR_BIT(CAN0_IF1ARB2_R, 15);		// CHECK // Ignore msg object for init MSGVAL = 0
	
	/* INITIALIZE MSG OBJECTS */
	/* Transmit Message Object */
	CAN0_IF1CMSK_R = 0x00000086;		// Bit6,5,4 = 0 .. Bit2= 1        check
	CAN0_IF1MSK2_R = 0;          		// Disable filtering for transmission 

	CAN0_IF1ARB2_R = 0x0000A01C;		// ID[12:2] = 7
	SET_BIT(CAN0_IF1MCTL_R, 7);		// EOB = 1
	SET_BIT(CAN0_IF1MCTL_R, 3);		// DLC = 8

	SET_BIT(CAN0_IF1ARB2_R, 15);		// MSGVAL = 1
	CAN0_BRPE_R = 0;			// CHECK // Baud Rate Prescaler Extension
	CLEAR_BIT(CAN0_CTL_R, 0);		// Clear INIT bit
}

void CAN_REG_WRITE (uint8 data)
{
	CAN0_IF1CMSK_R = 0x00000083;		// WRNRD, DATAA, DATAB = 1
	CAN0_IF1DA1_R = data;			// Assign data
	CAN0_IF1CRQ_R = 0x00000001;		// MSG NUM = 1
	CAN0_IF1MCTL_R = 0x00008100; 		// Set TXRQST, NEWDAT
}


void Can_Init( const Can_ConfigType* Config )
{
	#if (CAN_DEV_ERROR_DETECT == STD_ON)
		if(NULL_PTR == Config)
		{
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
							CAN_INIT_SID, CAN_E_PARAM_POINTER);
		}
		if(CAN_STATE != CAN_UNINIT)
		{
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
							CAN_INIT_SID, CAN_E_TRANSITION);
		}
		if(CAN_CONTROLLER_STATE != CAN_CS_UNINIT)
		{
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
							CAN_INIT_SID, CAN_E_TRANSITION);
		}
		else
	#endif
		{
			Can_ConfigStructPtr = Config;
            CAN_REG_INIT ();
                        
			/* SET STATES TO READY */
			CAN_STATE = CAN_READY;
			CAN_CONTROLLER_STATE = CAN_CS_STARTED;
		}
}

#if (CAN_VERSION_INFO_API == STD_ON)
void Can_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_GET_VERSION_INFO_SID, CAN_E_PARAM_POINTER);
	}
	else
#endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)CAN_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)CAN_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION;
	}
}
#endif


Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo )
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
	if(CAN_STATE == CAN_UNINIT)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_UNINIT);
		return CAN_NOT_OK;
	}
	if(NULL_PTR == PduInfo)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_POINTER);
		return CAN_NOT_OK;
	}
	if(Hth != Can_ConfigStructPtr->canHardwareObject[1]->CanObjectId)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_HANDLE);
		return CAN_NOT_OK;
	}
	if(PduInfo->length > 8)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_DATA_LENGTH);
		return CAN_NOT_OK;
	}
	else
#endif
	{
		if (mutex==1)
		{
  			return CAN_BUSY;
		}
		else
		{
			mutex=1;

			/* START OF CRITICAL SECTION */
			uint8 DATA = *(PduInfo->sdu);
			uint8 DLC = PduInfo->length;
			uint16 ID = PduInfo->id;

			CAN_REG_WRITE(DATA);
			/* SET ID & DATA 
			MB31_ID |= ((PduInfo->id)<<18);
			uint8 sdu_data = *(PduInfo->sdu);
			MB31_DATA_0 |= (uint32)(sdu_data << 24);
			/* CONFIGURE CS WORD 
			CLEAR_BIT(MB31_CS,21);					// IDE = 0
			CLEAR_BIT(MB31_CS,20);					// RTR = 0
			MB31_CS |= 0x0C000000;					// Activate message buffer (CODE= Transmit)
			MB31_CS |= ((PduInfo->length)<<16);		// set DLC
                        */
                        
			/* END OF CRITICAL SECTION */
			mutex=0;

			/* INDICATION OF SUCCESSFUL TRANSMISSION */
			CanIf_TxConfirmation(PduInfo->swPduHandle);
			return CAN_OK;
		}
	}
}

//void CanReceptionInterrupt()
//{
	/* RECEIVE PROCESS */

	//while(BIT_IS_SET(CAN_IFLAG1,31));	// buffer31 has successfully completed reception
	//Can_HwType Mailbox;
	//PduInfoType PduInfoPtr;
        
	/* READ MB31 CONTENTS 
	uint8 ControlStatus = (MB31_CS & 0x0F000000) >> 24;			// Read CODE
	uint8 Data = (MB31_DATA_0 & 0xFF000000) >> 24;				// Read DATA BYTE 0
	uint16 Id = (MB31_ID & 0x1FFC0000) >> 18;					// Read Standard ID
	uint8 Length = (MB31_CS & 0x000F0000) >> 16;				// Read DLC
        */
        
	/* ADD PDU INFO */
	//PduInfoPtr.SduDataPtr = &Data;
	//PduInfoPtr.SduLength =  Length;

	/* CLEAR MB31 FLAG */
	//CAN_IFLAG1 |= 0x80000000;

	/* READ TIMER TO UNLOCK MB */
	//uint32 Timer = CAN_TIMER;

	/* ADD MAILBOX INFO */
	//Mailbox.CanId = Id;
	//Mailbox.Hoh = Can_ConfigStructPtr->canHardwareObject[0]->CanObjectId;			// HRH
	//Mailbox.ControllerId = Can_ConfigStructPtr->canController->CanControllerId;

	/* CALLBACK FUNCTION */
	//CanLPduReceiveCalloutFunction(&Mailbox, &PduInfoPtr);

	/* SIGNAL THE END OF SERVICING THE INTERRUPT REQUEST */
	//INTC_EOIR0 = 0x00000000;
//}


/* OUR CAN_CTRL1 TO BE REMOVED IF NOT NEEDED
 * CAN_CTRL1 |= 0x00F90CA4;
 * ^^^ Can_Init() ^^^
 */

/* PINS FOR CAN TX & RX (AS PREVIOUS YEAR)
 * TX = 42 (PC10)
 * RX = 43 (PC11)
 * ^^^ Can_Init() ^^^
 */

/* MCR & CTRL1 WILL BE CHANGED IF WE WENT FOR PLAN B
 * VALUES ARE IN PBCFG.C FILE
 * ^^^ Can_Init() ^^^
 */

/* OUR IMPLEMENTATION IS DIFFERENT IN ORDER THAN PREVIOUS YEAR
 * IN CRITICAL SECTION
 * OUR REFERENCE IS DATASHEET PAGE 1789
 * ^^^ Can_Write() ^^^
 */
