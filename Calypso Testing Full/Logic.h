#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "Std_Types.h"

#define FOCUSED		(2U)
#define DEFOCUSED	(1U)
#define DROWSY		(0U)

#define LED_2		(0U)
#define LED_1		(8U)
#define LED_0		(16U)

void output (uint8 state);


#endif // LOGIC_H_INCLUDED
