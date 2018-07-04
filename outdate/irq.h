#ifndef __irq_h__
#define __irq_h__

#include "mcu.h"

#define RT_SysIrq_On() MemoryOr32(SYS_CTL0_REG, 0x1)
#define RT_SysIrq_Off()   MemoryAnd32(SYS_CTL0_REG, ~0x1)
#define RT_SysIrq_GetFlag()   MemoryRead32(SYS_IRQ_REG)
//|BIT|  0  | 1 | 2 | 3 | 4 | 5 | 6 |  7  | 8 |
//|IRQ|UART0|TC0|TC1|TC2|DBG|EXT|WDT|UART1|SPI|
/*********** External interrupt***********/
//********************************************************//
// void EXINT_Set(int en, int trigger)                 //
// Description:                                           //
// This function set the external interrupt               //
// "en" is the the number of the interrupt you want to    //
// open. en = 0:5 stands for INT0:INT5 representively.    //
// "trigger" is the trigger constrant."trigger" = 1 means //
// raising edge trigger."trigger"=0 means falling edge trigger //
//********************************************************//



/*********** External interrupt end*******/

#endif //__EXTIN_H__
