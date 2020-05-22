#include "uart.h"

void UART_Init(uint8 index){
	switch(index)
	{
		case 0:
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	
			UART0_CTL_R &= ~UART_CTL_UARTEN;
			UART0_IBRD_R = 520;    
			UART0_FBRD_R = 53;
			UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTA_AFSEL_R |= 0x03;
			GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) | (0x10 | 0x01);
			GPIO_PORTA_DEN_R |= 0x03;
			break;
	case 1 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	
			UART1_CTL_R &= ~UART_CTL_UARTEN;
			UART1_IBRD_R = 520;    
			UART1_FBRD_R = 53;
			UART1_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART1_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTB_AFSEL_R |= 0x03;
			GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00) | (0x10 | 0x01);
			GPIO_PORTB_DEN_R |= 0x03;
			break;
	case 2 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
			UART2_CTL_R &= ~UART_CTL_UARTEN;
			UART2_IBRD_R = 520;    
			UART2_FBRD_R = 53;
			UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART2_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTD_AFSEL_R |= 0xC0;
			GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF) | (0x10000000 | 0x01000000);
			GPIO_PORTD_DEN_R |= 0xC0;
			break;
	case 3 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
			UART3_CTL_R &= ~UART_CTL_UARTEN;
			UART3_IBRD_R = 520;    
			UART3_FBRD_R = 53;
			UART3_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART3_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTC_AFSEL_R |= 0xC0;
			GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF) | (0x10000000 | 0x01000000);
			GPIO_PORTC_DEN_R |= 0xC0;
			break;
	case 4 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R4;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
			UART4_CTL_R &= ~UART_CTL_UARTEN;
			UART4_IBRD_R = 520;    
			UART4_FBRD_R = 53;
			UART4_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART4_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTC_AFSEL_R |= 0x30;
			GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF) | (0x00100000 | 0x00010000);
			GPIO_PORTC_DEN_R |= 0x30;
			break;
	case 5 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
			UART5_CTL_R &= ~UART_CTL_UARTEN;
			UART5_IBRD_R = 520;    
			UART5_FBRD_R = 53;
			UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART5_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTE_AFSEL_R |= 0x30;
			GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF) | (0x00100000 | 0x00010000);
			GPIO_PORTE_DEN_R |= 0x30;
			break;
	case 6 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R6;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
			UART6_CTL_R &= ~UART_CTL_UARTEN;
			UART6_IBRD_R = 520;    
			UART6_FBRD_R = 53;
			UART6_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART6_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTD_AFSEL_R |= 0x30;
			GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF00FFFF) | (0x00100000 | 0x00010000);
			GPIO_PORTD_DEN_R |= 0x30;
			break;
	case 7 :
			SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
			SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
			UART7_CTL_R &= ~UART_CTL_UARTEN;
			UART7_IBRD_R = 520;    
			UART7_FBRD_R = 53;
			UART7_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
			UART7_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
			GPIO_PORTE_AFSEL_R |= 0x03;
			GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00) | (0x01 | 0x10);
			GPIO_PORTE_DEN_R |= 0x03;
			break;
	}
	
}

uint8 UART_Available(uint8 index)
{
	switch(index)
	{
		case 0 :
			return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 1 :
			return ((UART1_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
  	case 2 :
			return ((UART2_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 3 :
			return ((UART3_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 4 :
			return ((UART4_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 5 :
			return ((UART5_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 6 :
			return ((UART6_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		case 7 :
			return ((UART7_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
		  break ;
		
	}
}

uint8 UART_Read(uint8 index){
	switch(index)
	{
		case 0 :
		  while(UART_Available(0) != 1);
	    return (uint8)(UART0_DR_R&0xFF);
		  break;
		case 1 :
			while(UART_Available(1) != 1);
	    return (uint8)(UART1_DR_R&0xFF);
		  break;
		case 2 :
			while(UART_Available(2) != 1);
	    return (uint8)(UART2_DR_R&0xFF);
		  break;
		case 3 :
			while(UART_Available(3) != 1);
	    return (uint8)(UART3_DR_R&0xFF);
		case 4 :
			while(UART_Available(4) != 1);
	    return (uint8)(UART4_DR_R&0xFF);
		  break;
		case 5 :
			while(UART_Available(5) != 1);
	    return (uint8)(UART5_DR_R&0xFF);
		  break;
		case 6 :
			while(UART_Available(6) != 1);
	    return (uint8)(UART6_DR_R&0xFF);
		  break ;
		case 7 :
			while(UART_Available(7) != 1);
	    return (uint8)(UART7_DR_R&0xFF);
		  break;
	}
}

void UART_Write(uint8 index,uint8 data){
	
	switch(index)
	{
		case 0 :
			while((UART0_FR_R&UART_FR_TXFF) != 0);
	    UART0_DR_R = data;
		  break;
		case 1 :
			while((UART1_FR_R&UART_FR_TXFF) != 0);
	    UART1_DR_R = data;
		  break;
		case 2 :
			while((UART2_FR_R&UART_FR_TXFF) != 0);
	    UART2_DR_R = data;
		  break;
		case 3 :
			while((UART3_FR_R&UART_FR_TXFF) != 0);
	    UART3_DR_R = data;
		  break;
		case 4:
			while((UART4_FR_R&UART_FR_TXFF) != 0);
	    UART4_DR_R = data;
		  break;
		case 5:
			while((UART5_FR_R&UART_FR_TXFF) != 0);
	    UART5_DR_R = data;
		  break;
		case 6 :
			while((UART6_FR_R&UART_FR_TXFF) != 0);
	    UART6_DR_R = data;
		  break;
		case 7 :
			while((UART7_FR_R&UART_FR_TXFF) != 0);
	    UART7_DR_R = data;
		  break;
	}

}
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_Write(7,Str[i]);
		i++;
	}
}
void UART_receiveString(uint8 *Str)

{
	uint8 i = 0;
	Str[i] = UART_Read(7);
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_Read(7);
	}
	Str[i] = '\0';
}



/*
#include <stdbool.h>
#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "C:/Keil/EE319Kware/inc/hw_can.h"
#include "C:/Keil/EE319Kware/inc/hw_ints.h"
#include "C:/Keil/EE319Kware/inc/hw_memmap.h"
#include "can.h"
#include "gpio.h"
#include "interrupt.h"
#include "C:/Keil/EE319Kware/driverlib/pin_map.h"
#include "sysctl.h"
#include "uart.h"
#include "C:/Keil/EE319Kware/inc/hw_types.h"
#include "C:/Keil/EE319Kware/driverlib/debug.h"
#include "C:/Keil/EE319Kware/driverlib/rom.h"

#include "uart.h"

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}



//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	
    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
*/
