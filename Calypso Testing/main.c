#include <stdio.h>
#include <stdlib.h>

#include "Can.h"
int main()
{
    // INIT (1)
    Can_Init(&canConfigSet);

    // TRANSMIT PROCESS (2)
    uint8 t = 4;
    Can_ReturnType can_return;
    Can_PduType Pdu;
    Pdu.id = 1;
    Pdu.length = 8;
    Pdu.sdu = &t;
    Pdu.swPduHandle = 2;
    can_return = Can_Write(1,&Pdu);

    // RECEIVE PROCESS (3)
    CanReceptionInterrupt();

    return 0;
}
