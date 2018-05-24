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
#include "str.h"
#include "probe.h"

void sys_init();
void gdb();

int main2(void)
{
	int i = 0;
	sys_init();
	//_Uart_sync();
	CommSendHead2(BROADCAST_ID, BROADCAST_ID);
	puts("\rhello from MCU debugger\r");
	//setup probe usb
/*
	initialize_MAX();
	while (connected == 0) {
    		probe_setup();
		i++;
		if (i == 10000) {				
			break;
		}
	}
*/
	puts("setup done\r");
	CommSendTail();
	//end of probe setting
 	gdb();   
     return 0;
}	   


