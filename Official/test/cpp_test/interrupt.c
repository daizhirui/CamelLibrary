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
extern
void user_interrupt(void);
extern
void interrupt(void)
{
	//go to handler @0x10000008
	MemoryWrite(USER_INT, 0x1);
	user_interrupt();
}
