/*
 * Can_Cfg.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Rita
 */

#ifndef CAN_CFG_H_
#define CAN_CFG_H_

/*******************************************************************************
 *                      		 CanGeneral                                    *
 *******************************************************************************/

#define CAN_DEV_ERROR_DETECT 			STD_OFF
#define CanIndex 						(uint8)0x00		// Specifies the InstanceId of this module instance
#define CanLPduReceiveCalloutFunction	CanIf_RxIndication		// callout function after reception of L-PDU
#define CanMultiplexedTransmission		STD_OFF

#define CanPublicIcomSupport			STD_OFF
#define CanTimeoutDuration				(float32)1.0	// Specifies the maximum time for blocking function
														// until a timeout is detected. Unit is seconds.
#define CAN_VERSION_INFO_API			STD_ON

/*******************************************************************************
 *                      	  CanController                                    *
 *******************************************************************************/

//#define CanControllerActivation			STD_ON					// REMOVE ?
//#define CanControllerBaseAddress								// DON'T KNOW WHAT THIS IS ... REMOVE ?
//#define CanControllerId					(uint8)0x00		// controller ID which is unique in a given CAN Driver

//#define CanControllerDefaultBaudrate	CanControllerBaudrateConfig		// TO BE CHANGED

/*******************************************************************************
 *             			 CanControllerBaudrateConfig                           *
 *******************************************************************************/
/*
#define CanControllerBaudRate			(uint16)1400 					// TO BE CHANGED (decimal to hex)
#define CanControllerPropSeg			(uint8)0x64						// TO BE CHANGED
#define CanControllerSeg1				(uint8)0x64						// TO BE CHANGED
#define CanControllerSeg2				(uint8)0x64						// TO BE CHANGED
#define CanControllerSyncJumpWidth		(uint8)0x64						// TO BE CHANGED
#define CanHandleType					FULL
#define CanIdType						STANDARD
#define CanIdValue						(uint8)0x0A
#define CanObjectId						(uint16)100
#define CanObjectType					TRANSMIT
#define CanControllerRef				CanController
#define CanFilterMaskRef				CanFilterMask
#define CanMainFunctionRWPeriodRef		CanMainFunctionRWPeriods
*/
/*******************************************************************************
 *             					CanFilterMask               	               *
 *******************************************************************************/

#define CanFilterMaskValue				(uint16)100				// 	NOT FOUND IN CONTAINERS !! WHERE IS THAT


/*******************************************************************************
 *             						CanInit               	                   *
 *******************************************************************************/
/* MCR REGISTER CONFIG */
#define init_module_disable						(0U)
#define init_freeze_enable						(1U)
#define init_RX_FIFO_enable						(0U)
#define init_halt								(1U)	// To enter freeze mode
#define init_soft_reset							(0U)	// Ask if we have to reset register first
#define init_supervisor_mode					(1U)	// EDITED
#define init_warning_interrupt_enable			(0U)	// Not sure
#define init_self_reception_disable				(0U)	// For testing
#define init_IRMQ								(1U)
#define init_DMA_enable							(0U)
#define init_pretended_network_enable			(0U)
#define init_local_priority_enable				(1U)
#define init_abort_enable						(1U)
#define init_FD_operation_enable				(0U)
#define init_IDAM								(0U)
#define init_MAXMB								(10U)	// Random

/* CTRL1 REGISTER CONFIG */
#define init_prescaler_division_factor			(0x00)
#define init_resync_jump_width					(4U) 			// WE HAVE ONLY 2 BITS NEED TO BE CHECKED
#define init_phase_segmnet_1					(0x07)
#define init_phase_segmnet_2					(0x01)
#define init_bus_off_interrupt_mask				(0U)
#define init_error_interrupt_mask				(0U)
#define init_can_engine_clk_src					(0U)
#define init_loopback_mode						(0U)
#define init_TX_warning_interrupt_mask			(1U)
#define init_RX_warning_interrupt_mask			(1U)
#define init_can_bit_sampling					(1U)
#define init_bus_off_recovery					(0U)
#define init_timer_sync							(1U)
#define init_lowest_buffer_transmitted_first	(0U)
#define init_listen_only_mode					(0U)
#define init_prop_segment						(0x04)

/* CTRL2 REGISTER CONFIG */
#define init_ERRMSK_FAST						(0U)
#define init_bus_off_done_intmsk				(0U)
#define init_num_RX_fifo_filters				(0U)
#define init_TX_arbitration_start_delay			(2U)	// Random
#define init_mailboxes_reception_priority		(1U)
#define init_remote_request_storing				(1U)
#define init_EACEN								(1U)
#define init_timer_source						(0U)
#define init_protocol_exception_enable			(0U)
#define init_ISO_can_FD_enable					(1U)
#define init_edge_filter_disable				(0U)


#endif /* CAN_CFG_H_ */
