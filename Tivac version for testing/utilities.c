#include <stdbool.h>
#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/hw_can.h"
#include "C:/Keil/EE319Kware/inc/hw_ints.h"
#include "C:/Keil/EE319Kware/inc/hw_memmap.h"
#include "C:/Keil/EE319Kware/driverlib/can.h"
#include "C:/Keil/EE319Kware/driverlib/gpio.h"
#include "C:/Keil/EE319Kware/driverlib/interrupt.h"
#include "C:/Keil/EE319Kware/driverlib/pin_map.h"
#include "C:/Keil/EE319Kware/driverlib/sysctl.h"
#include "uart.h"


#include "C:/Keil/EE319Kware/inc/hw_types.h"
#include "C:/Keil/EE319Kware/driverlib/debug.h"
#include "C:/Keil/EE319Kware/driverlib/rom.h"

#include "utilities.h"

//*****************************************************************************
//
// This function provides a 1 second delay using a simple polling method.
//
//*****************************************************************************
void
SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}
