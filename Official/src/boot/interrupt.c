//################################################################
// TITLE: debugger
// AUTHOR: Bill
// DATE CREATED: 09/26/2015
// FILENAME: gdb.c
// COPYRIGHT: Copyright (C) Camel Microelectronics, Inc.
// DESCRIPTION:
// Rev No.: V1.0
//
//
//
//################################################################

#include "mcu.h"

void user_interrupt(void);
void before_user_interrupt(void);
void interrupt(void)
{
	//go to handler @0x10000008
	MemoryWrite(USER_INT, 0x1);
	user_interrupt();
}
