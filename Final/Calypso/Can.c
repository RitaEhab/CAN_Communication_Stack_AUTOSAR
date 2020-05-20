#include "Can.h"
#include "Common_Macros.h"
#include "CanIf_Cbk.h"

STATIC const Can_ConfigType* Can_ConfigStructPtr = NULL_PTR;
STATIC Can_StateType CAN_STATE = CAN_UNINIT;
STATIC Can_ControllerStateType CAN_CONTROLLER_STATE = CAN_CS_UNINIT;
STATIC uint8 mutex =0;

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
            uint32 CAN_CTRL1 = 0x00000080;
            CAN_CTRL1 |= ((Config->canController->canControllerBaudrateConfig->CanControllerSyncJumpWidth) << 22);
			CAN_CTRL1 |= ((Config->canController->canControllerBaudrateConfig->CanControllerSeg1) << 19);
			CAN_CTRL1 |= ((Config->canController->canControllerBaudrateConfig->CanControllerSeg2) << 16);
			CAN_CTRL1 |= ((Config->canController->canControllerBaudrateConfig->CanControllerPropSeg) << 0);

			CAN_MCR |= 0x0083300A;
			CAN_CTRL1 = 0x00000080;		// (PresDiv)


			/* MESSAGE BUFFERS INIT */
			MB31_CS &= ~(0x0F000000);		// Control and Status word of all message buffers is initialized
												// CODE = INACTIVE

			uint8 i;
			for (i=0; i<96; i++)
			{
				*MB &= ~(0x0F000000);			//		INITIALIZE ALL 96 BUFFERS
				MB += 4;
			}
            // ^^^ CHECK ^^^

			/* RECEIVE MAILBOX INIT */
			MB31_ID = 0x0004000;				// Frame Identifier = 1
			MB31_CS |= 0x04000000;				// CODE = EMPTY

			/* MASK REGISTERS INIT */
			CAN_RXMGMASK = 0x80000000;			// Enable MB31
			CAN_IMASK1 = 0x00000001;
			CAN_CTRL2 |= 0x00171000;			// Optional

			/* SIUL2 INIT */
			SIUL2_MSCR42 = 0x32000001;			// Tx reg
			SIUL2_MSCR43 = 0x00080000;			// Rx reg
			SIUL2_IMCR189 = 0x00000003;			// Rx SSS

			/* EXIT FREEZE MODE */
			CLEAR_BIT(CAN_MCR,28);				// (Halt = 0)

			/* INTERRUPT INIT */
			CLEAR_BIT(INTC_BCR,0);				// Software vector mode
			CLEAR_BIT(INTC_MPROT,0);
			INTC_CPR0 |= 0x0000000F;
			INTC_IACKR0 = 0;
			INTC_SSCIR0 = 0x00000001;			// Check
			INTC_SSCIR10= 0x00000001;			// Check
			//IVPR=0x00000000;
			GPR_CTL1=0x00000000;				// Locate vector table in address ZERO

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
			/* SET ID & DATA */
			MB31_ID |= ((PduInfo->id)<<18);
			uint8 sdu_data = *(PduInfo->sdu);
			MB31_DATA_0 |= (uint32)(sdu_data << 24);

			/* CONFIGURE CS WORD */
			CLEAR_BIT(MB31_CS,21);					// IDE = 0
			CLEAR_BIT(MB31_CS,20);					// RTR = 0
			MB31_CS |= 0x0C000000;					// Activate message buffer (CODE= Transmit)
			MB31_CS |= ((PduInfo->length)<<16);		// set DLC

			/* END OF CRITICAL SECTION */
			mutex=0;

			/* INDICATION OF SUCCESSFUL TRANSMISSION */
			CanIf_TxConfirmation(PduInfo->swPduHandle);
			return CAN_OK;
		}
	}
}

__interrupt CanReceptionInterrupt()
{
	/* RECEIVE PROCESS */

	while(BIT_IS_SET(CAN_IFLAG1,31));	// buffer31 has successfully completed reception
	Can_HwType Mailbox;
	PduInfoType PduInfoPtr;

	/* READ MB31 CONTENTS */
	uint8 ControlStatus = (MB31_CS & 0x0F000000) >> 24;			// Read CODE
	uint8 Data = (MB31_DATA_0 & 0xFF000000) >> 24;				// Read DATA BYTE 0
	uint16 Id = (MB31_ID & 0x1FFC0000) >> 18;					// Read Standard ID
	uint8 Length = (MB31_CS & 0x000F0000) >> 16;				// Read DLC

	/* ADD PDU INFO */
	PduInfoPtr.SduDataPtr = &Data;
	PduInfoPtr.SduLength =  Length;

	/* CLEAR MB31 FLAG */
	CAN_IFLAG1 |= 0x80000000;

	/* READ TIMER TO UNLOCK MB */
	uint32 Timer = CAN_TIMER;

	/* ADD MAILBOX INFO */
	Mailbox.CanId = Id;
	Mailbox.Hoh = Can_ConfigStructPtr->canHardwareObject[0]->CanObjectId;			// HRH
	Mailbox.ControllerId = Can_ConfigStructPtr->canController->CanControllerId;

	/* CALLBACK FUNCTION */
	CanLPduReceiveCalloutFunction(&Mailbox, &PduInfoPtr);

	/* SIGNAL THE END OF SERVICING THE INTERRUPT REQUEST */
	INTC_EOIR0 = 0x00000000;
}


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
