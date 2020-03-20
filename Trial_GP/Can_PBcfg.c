/*
 * Can_PBcfg.c
 *
 *  Created on: Feb 8, 2020
 *      Author: Rita
 */

#include "Can_Cfg.h"
#include "Can.h"

const Can_ConfigType Can_Configuration =
{
		init_module_disable, init_freeze_enable, init_RX_FIFO_enable, init_halt,
		init_soft_reset, init_supervisor_mode, init_warning_interrupt_enable,
		init_self_reception_disable, init_IRMQ, init_DMA_enable, init_pretended_network_enable,
		init_local_priority_enable, init_abort_enable, init_FD_operation_enable,
		init_IDAM, init_MAXMB
};
