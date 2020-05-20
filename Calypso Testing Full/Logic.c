#include "Logic.h"
//#include "Micro_Registers.h"

void output (uint8 state)
{
	if(state == FOCUSED)
	{
		/*
		SET_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
        */
        printf("FOCUSED");
	}
	else if(state == DEFOCUSED)
	{
	    /*
		SET_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
        */
        printf("DEFOCUSED");
	}
	else if(state == DROWSY)
	{
	    /*
		SET_BIT(SIUL2_GPDO_0, LED_0);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
        */
        printf("DROWSY");
	}
	else
	{
		printf("ERROR");
	}
}
