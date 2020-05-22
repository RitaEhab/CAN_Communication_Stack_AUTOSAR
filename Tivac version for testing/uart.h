#ifndef __UART_E_H__
#define	__UART_E_H__

#include "tm4c123gh6pm.h"

void UART_Init(uint8 index);
uint8 UART_Available(uint8 index);
uint8 UART_Read(uint8 index);
void UART_Write(uint8 index,uint8 data);
void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str);


#endif // __UART_H__

/*
void InitConsole(void);
void ConfigureUART(void);
*/
