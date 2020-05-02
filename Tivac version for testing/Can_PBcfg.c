#include "Can_PBcfg.h"
#include "Can_Cfg.h"

#include "Can_PBcfg.h"
#include "Can_Cfg.h"

#include "C:/Keil/EE319Kware/inc/hw_memmap.h"



#include "C:/Keil/EE319Kware/driverlib/gpio.h"
#include "C:/Keil/EE319Kware/driverlib/pin_map.h"
#include "C:/Keil/EE319Kware/driverlib/sysctl.h"

Can_ControllerConfigType Can0ControllerConfig = {
	SYSCTL_PERIPH_GPIOB,
	GPIO_PB4_CAN0RX,
	GPIO_PB5_CAN0TX,
	GPIO_PORTB_BASE,
	GPIO_PIN_4 | GPIO_PIN_5,
	SYSCTL_PERIPH_CAN0,
	CAN0_BASE,
	500000,
	1,
	0,
	1
};
const Can_ControllerConfigType *CanControllersConfigs[2] = {&Can0ControllerConfig, 0};
const Can_ConfigType CanConfig = {CanControllersConfigs};

const uint32 Can_Bases[2] = {CAN0_BASE, CAN1_BASE};

//ID of controller based on hth as an index
const uint32 Can_Controllers[2] = {0, 0};