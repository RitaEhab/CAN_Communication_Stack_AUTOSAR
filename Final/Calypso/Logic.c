#include "Logic.h"
#include "Micro_Registers.h"

void output (uint8 state)
{
	if(state == FOCUSED)
	{
	    // Led 2 on
		SET_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
	}
	else if(state == DEFOCUSED)
	{
	    // Led 1 on
		SET_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
	}
	else if(state == DROWSY)
	{
	    // Led 0 on
		SET_BIT(SIUL2_GPDO_0, LED_0);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
	}
	else
	{
		// error
	}
}
