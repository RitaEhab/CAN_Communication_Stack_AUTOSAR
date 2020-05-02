/*
 * Logic.c
 *
 *  Created on: May 1, 2020
 *      Author: Rita
 */

#include "Logic.h"
#include "Micro_Registers.h"

void output (uint8 state)
{
	if(state == FOCUSED)
	{
		SET_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
	}
	else if(state == DEFOCUSED)
	{
		SET_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
		CLEAR_BIT(SIUL2_GPDO_0, LED_0);
	}
	else if(state == DROWSY)
	{
		SET_BIT(SIUL2_GPDO_0, LED_0);
		CLEAR_BIT(SIUL2_GPDO_0, LED_1);
		CLEAR_BIT(SIUL2_GPDO_0, LED_2);
	}
	else
	{
		// printf("ERROR");
	}
}
