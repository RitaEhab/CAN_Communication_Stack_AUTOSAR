#include "Can.h"
#include "CanIf.h"
#include "PduR.h"
#include "Com.h"
#include "uart.h"

int main()
{
    // Initialize all modules
    Com_Init(&com_ConfigType);
    PduR_Init(&pduR_PBConfigType);
    CanIf_Init(&canIf_ConfigType);
    Can_Init(&canConfigSet);
    
    UART_Init(7);
    
    while (1)
    {
        uint8 data = UART_Read(7);              // Recieve data from putty
        uint8 ret = Com_SendSignal(0, &data);   // Send data to Com
    }
    return 0;
}
