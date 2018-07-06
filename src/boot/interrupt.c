/**
* @file interrupt.c
* @author Zhirui Dai
* @date 6 Jul 2018
* @copyright 2018 Zhirui
* @brief Interrupt function
* @note  This file is already merged into isr.s !!
*/
#include "mcu.h"

void user_interrupt(void);

void interrupt(void)
{
	//go to handler @0x10000008
	MemoryWrite32(USER_INT, 0x1);
	user_interrupt();
}
