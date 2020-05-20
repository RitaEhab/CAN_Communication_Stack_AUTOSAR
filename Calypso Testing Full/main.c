#include <stdio.h>
#include <stdlib.h>

#include "Can.h"
#include "CanIf.h"
#include "PduR.h"
#include "Com.h"

int main()
{
    Com_Init(&com_ConfigType);
    PduR_Init(&pduR_PBConfigType);
    CanIf_Init(&canIf_ConfigType);

    /*
    uint8 d = 1;
    PduInfoType PduInfoPtr;
    PduInfoPtr.SduLength = 8;
    PduInfoPtr.SduDataPtr = &d;
    */


    // INIT (1)
    Can_Init(&canConfigSet);
    uint8 d = 2;
    uint8 r = Com_SendSignal(0, &d);
    printf("COM SEND SIGNAL RETURNS %d\n\n\n", r);

    //Can_ReturnType r = CanIf_Transmit(3, &PduInfoPtr);
    //printf("CanIf Transmit returns %d", r);

    // TRANSMIT PROCESS (2)
    /*
    uint8 t = 4;
    Can_ReturnType can_return;
    Can_PduType Pdu;
    Pdu.id = 1;
    Pdu.length = 8;
    Pdu.sdu = &t;
    Pdu.swPduHandle = 3;
    can_return = Can_Write(1,&Pdu);
    printf ("Can write returns %x", can_return);
    */
    // RECEIVE PROCESS (3)
    CanReceptionInterrupt();

    return 0;
}
