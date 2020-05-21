#include "Can.h"
#include "CanIf.h"
#include "PduR.h"
#include "Com.h"

int main()
{
    // Initialize all modules
    Com_Init(&com_ConfigType);
    PduR_Init(&pduR_PBConfigType);
    CanIf_Init(&canIf_ConfigType);
    Can_Init(&canConfigSet);

    return 0;
}
