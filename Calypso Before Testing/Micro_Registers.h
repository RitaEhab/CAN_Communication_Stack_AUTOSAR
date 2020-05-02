/*
 * Micro_Registers.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Rita
 */

#ifndef MICRO_REGISTERS_H_
#define MICRO_REGISTERS_H_

#define CAN_MCR        		(*((volatile unsigned long *)0xFFEC0000))
#define CAN_CTRL1        	(*((volatile unsigned long *)0xFFEC0004))
#define CAN_TIMER        	(*((volatile unsigned long *)0xFFEC0008))
#define CAN_RXMGMASK        (*((volatile unsigned long *)0xFFEC0010))
#define CAN_RX14MASK        (*((volatile unsigned long *)0xFFEC0014))
#define CAN_RX15MASK        (*((volatile unsigned long *)0xFFEC0018))
#define CAN_ECR        		(*((volatile unsigned long *)0xFFEC001C))
#define CAN_ESR1        	(*((volatile unsigned long *)0xFFEC0020))
#define CAN_IMASK1        	(*((volatile unsigned long *)0xFFEC0024))
#define CAN_IMASK2        	(*((volatile unsigned long *)0xFFEC0028))

#define CAN_IFLAG2        	(*((volatile unsigned long *)0xFFEC002C))
#define CAN_IFLAG1        	(*((volatile unsigned long *)0xFFEC0030))
#define CAN_CTRL2        	(*((volatile unsigned long *)0xFFEC0034))
#define CAN_ESR2        	(*((volatile unsigned long *)0xFFEC0038))
#define CAN_CRCR       		(*((volatile unsigned long *)0xFFEC0044))
#define CAN_RXFGMASK      	(*((volatile unsigned long *)0xFFEC0048))
#define CAN_RXFIR        	(*((volatile unsigned long *)0xFFEC004C))
#define CAN_CBT        		(*((volatile unsigned long *)0xFFEC0050))
#define CAN_IMASK3        	(*((volatile unsigned long *)0xFFEC006C))
#define CAN_IFLAG3     		(*((volatile unsigned long *)0xFFEC0074))

#define CAN_RXIMR0        	(*((volatile unsigned long *)0xFFEC0880))
#define CAN_CTRL1_PN        (*((volatile unsigned long *)0xFFEC0B00))
#define CAN_WU_MTC        	(*((volatile unsigned long *)0xFFEC0B08))
#define CAN_FLT_ID1        	(*((volatile unsigned long *)0xFFEC0B0C))
#define CAN_PL1_LO        	(*((volatile unsigned long *)0xFFEC0B14))
#define CAN_PL1_HI        	(*((volatile unsigned long *)0xFFEC0B18))
#define CAN_FLT_ID2_IDMASK  (*((volatile unsigned long *)0xFFEC0B1C))
#define CAN_PL2_PLMASK_LO   (*((volatile unsigned long *)0xFFEC0B20))
#define CAN_PL2_PLMASK_HI   (*((volatile unsigned long *)0xFFEC0B24))
#define CAN_WMB0_CS        	(*((volatile unsigned long *)0xFFEC0B40))

#define CAN_WMB0_ID        	(*((volatile unsigned long *)0xFFEC0B44))
#define CAN_WMB0_D03        (*((volatile unsigned long *)0xFFEC0B48))
#define CAN_WMB0_D47        (*((volatile unsigned long *)0xFFEC0B4C))
#define CAN_WMB1_CS        	(*((volatile unsigned long *)0xFFEC0B50))
#define CAN_WMB1_ID        	(*((volatile unsigned long *)0xFFEC0B54))
#define CAN_WMB1_D03        (*((volatile unsigned long *)0xFFEC0B58))
#define CAN_WMB1_D47        (*((volatile unsigned long *)0xFFEC0B5C))
#define CAN_WMB2_CS        	(*((volatile unsigned long *)0xFFEC0B60))
#define CAN_WMB2_ID        	(*((volatile unsigned long *)0xFFEC0B64))
#define CAN_WMB2_D03        (*((volatile unsigned long *)0xFFEC0B68))

#define CAN_WMB2_D47        (*((volatile unsigned long *)0xFFEC0B6C))
#define CAN_WMB3_CS        	(*((volatile unsigned long *)0xFFEC0B70))
#define CAN_WMB3_ID        	(*((volatile unsigned long *)0xFFEC0B74))
#define CAN_WMB3_D03        (*((volatile unsigned long *)0xFFEC0B78))
#define CAN_WMB3_D47        (*((volatile unsigned long *)0xFFEC0B7C))
#define CAN_FDCTRL        	(*((volatile unsigned long *)0xFFEC0C00))
#define CAN_FDCBT        	(*((volatile unsigned long *)0xFFEC0C04))
#define CAN_FDCRC        	(*((volatile unsigned long *)0xFFEC0C08))

#define GPR_CTL1        	(*((volatile unsigned long *)0xFFF94010))

#define MB31_CS				(*((volatile unsigned long *)0xFFEC0270))
#define MB31_ID 			(*((volatile unsigned long *)0xFFEC0274))
#define MB31_DATA_0			(*((volatile unsigned long *)0xFFEC0278))
#define MB31_DATA_4			(*((volatile unsigned long *)0xFFEC027C))

#define MB					((volatile unsigned long *)0xFFEC0080)

#define INTC_BCR        	(*((volatile unsigned long *)0xFC040000))
#define INTC_MPROT        	(*((volatile unsigned long *)0xFC040004))
#define INTC_CPR0        	(*((volatile unsigned long *)0xFC040010))
#define INTC_IACKR0        	(*((volatile unsigned long *)0xFC040020))
#define INTC_EOIR0        	(*((volatile unsigned long *)0xFC040030))
#define INTC_SSCIR0        	(*((volatile unsigned long *)0xFC040040))
#define INTC_SSCIR10        (*((volatile unsigned long *)0xFC04004A))
#define INTC_BCR        	(*((volatile unsigned long *)0xFC040000))

#define SIUL2_MSCR42        (*((volatile unsigned long *)0xFFFC02E8))
#define SIUL2_MSCR43        (*((volatile unsigned long *)0xFFFC02EC))
#define SIUL2_IMCR189       (*((volatile unsigned long *)0xFFFC0534))

#define SIUL2_GPDO_0		(*((volatile unsigned long *)0xFFFC1300))

#endif /* MICRO_REGISTERS_H_ */
