/*
 * Can_GeneralTypes.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Rita
 */

#ifndef CAN_GENERALTYPES_H_
#define CAN_GENERALTYPES_H_

#include "Std_Types.h"

/* MOVED FROM COMSTACK_TYPES.H*/
/* Maximum number of PDUs (Protocol data unit) used within one software module */
typedef uint8 PduIdType;

typedef struct{
	/* MCR REGISTER OPTIONS */
	uint8 module_disable;
	uint8 freeze_enable;
	uint8 RX_FIFO_enable;
	uint8 halt;
	uint8 soft_reset;
	uint8 supervisor_mode;
	uint8 warning_interrupt_enable;
	uint8 self_reception_disable;
	uint8 IRMQ;							// Individual RX masking and Queue enable
	uint8 DMA_enable;
	uint8 pretended_network_enable;
	uint8 local_priority_enable;
	uint8 abort_enable;
	uint8 FD_operation_enable;
	uint8 IDAM;							// ID Acceptance Mode
	uint8 MAXMB;						// Number of last message buffer

	/* CTRL1 REGISTER OPTIONS */
	uint8 prescaler_division_factor;
	uint8 resync_jump_width;
	uint8 phase_segmnet_1;
	uint8 phase_segmnet_2;
	uint8 bus_off_interrupt_mask;
	uint8 error_interrupt_mask;
	uint8 can_engine_clk_src;
	uint8 loopback_mode;
	uint8 TX_warning_interrupt_mask;
	uint8 RX_warning_interrupt_mask;
	uint8 can_bit_sampling;
	uint8 bus_off_recovery;
	uint8 timer_sync;
	uint8 lowest_buffer_transmitted_first;
	uint8 listen_only_mode;
	uint8 prop_segment;

	/* CTRL2 REGISTER OPTIONS */
	uint8 ERRMSK_FAST;
	uint8 bus_off_done_intmsk;
	uint8 num_RX_fifo_filters;
	uint8 TX_arbitration_start_delay;
	uint8 mailboxes_reception_priority;
	uint8 remote_request_storing;
	uint8 EACEN;
	uint8 timer_source;
	uint8 protocol_exception_enable;
	uint8 ISO_can_FD_enable;
	uint8 edge_filter_disable;
} Can_ConfigType;


typedef struct{


} Can_ControllerBaudrateConfigType;


typedef struct{
	PduIdType swPduHandle;
	uint8 length;
	uint8* sdu;
} Can_PduType;

typedef uint16 Can_IdType;
typedef uint16 Can_HwHandleType;	// Don't know whether to use or not

typedef enum Can_StateTransitionType{
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

typedef enum Can_ReturnType{
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

typedef enum Can_StateType{
	CAN_READY,
	CAN_UNINIT
} Can_StateType;

typedef enum Can_ControllerStateType {
	CAN_CS_UNINIT = 0x00,
	CAN_CS_STARTED = 0x01,
	CAN_CS_STOPPED = 0x02,
	CAN_CS_SLEEP = 0x03
} Can_ControllerStateType;

typedef struct{
	Can_IdType CanId;
	Can_HwHandleType Hoh;
	uint8 ControllerId;
} Can_HwType;

					// NOT COMPLETE !!
typedef struct {
	//CanHandleType;
	//CanObjectId;
} CanHardwareObject;

#endif /* CAN_GENERALTYPES_H_ */
