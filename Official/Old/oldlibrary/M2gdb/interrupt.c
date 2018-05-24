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


void user_interrupt(void);
//char __mac_id = (char)BROADCAST_ID;
/*
void flashWrite(unsigned long value, unsigned long address)
{
	FuncPtr2 funcptr;
	funcptr = (FuncPtr2)0x2d8;
	funcptr(value, address);
}

void flashErase(unsigned long address)
{
	unsigned long addr;
	FuncPtr1 funcptr;
	funcptr =  (FuncPtr1)0x30c;
	addr = (((((address>>16)&0xF)|0x1010)<<16) + (address&0xFFFF));
	funcptr(addr);
}

char getMAC()
{
	return MemoryRead32(MAC_ID);
}

void setMAC(char id)
{
	//MemoryWrite32(MAC_ID, id);
	flashWrite(id, MAC_ID);
}
*/
void _Uart_sync()
{
	int i, start, pre, len;
	char tmp[SYNC_LEN];
	char ch;
	int val[SYNC_LEN];
	int state1, state2;
	int state = MemoryRead32(UART_OSC_REG);
	state &= ~(7<<4); //clear the uart freq adjust reg
	val[0] = 6;
	val[1] = 5;
	val[2] = 4;
	val[3] = 2;
	val[4] = 7;
	val[5] = 1;
	val[6] = 0;
	val[7] = 3;
	for (i = 0; i < SYNC_LEN; i++) {
		state1 = (state | (val[i]<<4));
		MemoryWrite32(UART_OSC_REG, state1);
		//puts("SYNC\r");
		tmp[i] = getch();
	}
	pre = -1;
	len = 0;
	start = 0;
	for (i = 0; i < SYNC_LEN; i++) {
		if (pre < 0 && tmp[i] == PAC_HEAD)
			pre = i;
		else if (pre >= 0 && tmp[i] != PAC_HEAD) {
			if (len < (i - pre)) {
				len = i - pre;
				start = pre;
			}
			pre = -1;
		}
	}
	if (len == 0) //all are good
		len = 8;
	start = start + len/2;
	state1 = (state | (val[start]<<4));
	MemoryWrite32(UART_OSC_REG, state1);
	puts("\rUART SYNC DONE!\r");
	/*
	for (i = 0; i < SYNC_LEN; i++){
		state2 = (state | (val[i]<<4));
		puts(xtoa(state2));
		puts(" ");
		puts(xtoa(tmp[i]));
		puts("\r");
	}
	puts(xtoa(start));
	puts("\r");
	puts(xtoa(len));
	puts("\r");
	puts(xtoa(state));
	puts("\r");
	puts(xtoa(state1));
	puts("\r");
	*/
}

void sys_init()
{
        MemoryWrite(INT_CTL2_REG, 0xff);    // ex int high enable set
        MemoryWrite(INT_CLR_REG,  0xff);    // ex int clear
        MemoryWrite(INT_CTL0_REG, 0x00);    // ex int DISABLE set
        MemoryWrite(SYS_IOCTL_REG, 0x0000); // This 16-bit reg is used as menu record pointer
        MemoryWrite(SD_CTL_REG, 0x0);
        MemoryWrite(INT_COUNT, 0x0); //initialize the reg for recording number of interrupts in the path, 
                                     //it determines where SP is stored for each interrupt
        MemoryWrite(USER_INT, 0x0); //initialize the reg to choose gdb() or user interrupt function when interrupt is generated
//	  __mac_id = getMAC();
}

void interrupt(void)
{
	//go to handler @0x10000008
	MemoryWrite(USER_INT, 0x1);
	user_interrupt();
}


