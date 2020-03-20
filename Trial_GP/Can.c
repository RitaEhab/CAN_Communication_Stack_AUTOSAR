/*
 * Can.c
 *
 *  Created on: Feb 7, 2020
 *      Author: Rita
 */

#include "Can.h"
#include "Common_Macros.h"
#include "CanIf_Cbk.h"

STATIC const Can_ConfigType* Can_ConfigStructPtr = NULL_PTR;
STATIC Can_StateType CAN_STATE = CAN_UNINIT;
STATIC uint8 data;

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
		else
	#endif
		{
			Can_ConfigStructPtr = Config;		// TO BE EDITED Config struct to have instances, Can_ConfigStructPtr NOT Can_ConfigType BUT smaller

			CAN_MCR |= 1<<25;					// Enable SOFT RESET
			while (BIT_IS_SET(CAN_MCR,25));		// Make sure SOFT RESET is done
			SET_BIT(CAN_MCR,31);				// Enter disable mode

			CLEAR_BIT(CAN_CTRL1,13);			// Assign clock source
			CLEAR_BIT(CAN_MCR,31);				// Enter enable mode

			// FRZ, HALT = IS IT DONE AUTOMATICALLY OR MUST BE SET MANUALLY?
			SET_BIT(CAN_MCR,30);				// Set freeze enable
			SET_BIT(CAN_MCR,28);				// Enter freeze mode

			while (BIT_IS_CLEAR(CAN_MCR,27) && BIT_IS_CLEAR(CAN_MCR,24));	// Check we entered freeze mode successfully FRZACK, NTRDY
			CAN_MCR |= 0x0083300A;
			/*
			CAN_MCR =((Can_ConfigStructPtr->RX_FIFO_enable<<29)		| (Can_ConfigStructPtr->supervisor_mode<<23) |
					  (Can_ConfigStructPtr->warning_interrupt_enable<<21) | (Can_ConfigStructPtr->self_reception_disable<<17)|
					  (Can_ConfigStructPtr->IRMQ<<16) 				| (Can_ConfigStructPtr->DMA_enable<<15)|
					  (Can_ConfigStructPtr->pretended_network_enable<<14) | (Can_ConfigStructPtr->local_priority_enable<<13)|
					  (Can_ConfigStructPtr->abort_enable<<12) 		| (Can_ConfigStructPtr->FD_operation_enable<<11)|
					  (Can_ConfigStructPtr->IDAM<<9) 				| (Can_ConfigStructPtr->MAXMB<<0));
			*/
			CAN_CTRL1 |= 0x00F90CA4;
			/*
			CAN_CTRL1 =((Can_ConfigStructPtr->prescaler_division_factor<<24) | (Can_ConfigStructPtr->resync_jump_width<<22) |
						(Can_ConfigStructPtr->phase_segmnet_1<<19) 			| (Can_ConfigStructPtr->phase_segmnet_2 <<16) |
						(Can_ConfigStructPtr->bus_off_interrupt_mask<<15) 	|(Can_ConfigStructPtr->error_interrupt_mask<<14) |
						(Can_ConfigStructPtr->can_engine_clk_src<<13) 		| (Can_ConfigStructPtr->loopback_mode<<12) |
						(Can_ConfigStructPtr->TX_warning_interrupt_mask<<11) | (Can_ConfigStructPtr->RX_warning_interrupt_mask<<10) |
						(Can_ConfigStructPtr->can_bit_sampling<<7) 			| (Can_ConfigStructPtr->bus_off_recovery<<6) |
						(Can_ConfigStructPtr->timer_sync<<5) 				| (Can_ConfigStructPtr->lowest_buffer_transmitted_first<<4) |
						(Can_ConfigStructPtr->listen_only_mode<<3) 			| (Can_ConfigStructPtr->prop_segment<<0)  );
			*/
			CAN_RXMGMASK = 0x80000000;			 // Enable MB31
			CAN_IMASK1 = 0x00000001;

			/* MAILBOX INIT */
			CLEAR_BIT(CAN_MCR,12);				// Deassert abort enable
			MSG_BUFF_PARAM |= 0b0000 << 26;		// Set CODE as INACTIVE >> To be checked
			MSG_BUFF_ID |= 1 << 16;				// Set ID to be 1
			MSG_BUFF_PARAM |= 0b0100 << 26;		// Set CODE as EMPTY

			CAN_CTRL2 |= 0x00171000;
			/*
			CAN_CTRL2 =((Can_ConfigStructPtr->ERRMSK_FAST<<31) 				| (Can_ConfigStructPtr->bus_off_done_intmsk<<30) |
						(Can_ConfigStructPtr->num_RX_fifo_filters<<27) 		| (Can_ConfigStructPtr->TX_arbitration_start_delay <<23) |
						(Can_ConfigStructPtr->mailboxes_reception_priority<<18) 	|(Can_ConfigStructPtr->remote_request_storing<<17) |
						(Can_ConfigStructPtr->EACEN<<16) 					| (Can_ConfigStructPtr->timer_source<<15) |
						(Can_ConfigStructPtr->protocol_exception_enable<<14) | (Can_ConfigStructPtr->ISO_can_FD_enable<<12) |
						(Can_ConfigStructPtr->edge_filter_disable<<11) );
			*/
			CLEAR_BIT(CAN_MCR,28);				// Disable freeze mode
			CAN_STATE = CAN_READY;
			CLEAR_BIT(INTC_BCR,0);				// Software vector mode
			CLEAR_BIT(INTC_MPROT,0);
			INTC_CPR0 |= 0x0000000F;
			INTC_IACKR0 = 0;
			INTC_SSCIR0 = 0x00000001;			// ASKKKKKKKKK
			INTC_SSCIR10= 0x00000001;			// ASKKKKKKKKK
			//IVPR=0x00000000;
			GPR_CTL1=0x00000000;				// Locate vector table in address ZERO
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
		return E_NOT_OK;
	}
	if(NULL_PTR == PduInfo)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	if(Hth != 0) // page 68				// CHECK IF NOT CONFIGURED
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_HANDLE);
		return E_NOT_OK;
	}
	if(PduInfo->length > 8)
	{
		/* Report to DET  */
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,
						CAN_WRITE_SID, CAN_E_PARAM_DLC);
		return E_NOT_OK;
	}
	else
#endif
	{
		// Function write controller
		CanIf_TxConfirmation(PduInfo->swPduHandle); //indicates successful transmission
		return E_OK;
	}
}

__interrupt void CanReceptionInterrupt()

{
	/* RECEIVE PROCESS */
	while(BIT_IS_SET(MSG_BUFF_PARAM,24));
	data = (MSG_BUFF_DATA_0 & 0xFF000000) >> 24;				// DATA BYTE 0
	CAN_IFLAG1 |= 0x80000000;

	////////////////////////////////////////////

	/* OPERATION ON DATA */

	////////////////////////////////////////////
// add your code here and call CanIf_RxIndication at the end
// with ID, DLC and pointer to the L-SDU buffer as parameter.
	INTC_EOIR0 = 0x00000000;
}
