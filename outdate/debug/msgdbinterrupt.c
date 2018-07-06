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

//typedef void (*FuncPtr)(void);
//typedef void (*FuncPtr2)(unsigned long, unsigned long);
//typedef void (*FuncPtr1)(unsigned long);
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
	CommSendHead(STUDIO_ID);
	puts("\rUART SYNC DONE!\r");
	CommSendTail();
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
	 // __mac_id = getMAC();
}

// '\r' is the special char to indicate the end of the one protocol
//1. w <addr> <count> <v1> ... <vn>\r  //write <count> number of values to memory block from <addr>
void _w_func()
{
     int i;
     unsigned long address, value, count;
	address = getnum();
	count = getnum();
	for (i = 0; i < count; i++) {
        	value = getnum();
           MemoryWrite32(address, value);
 		address += 4;
	}
	CommRecvTail();
	CommSendHead(STUDIO_ID);
	putc_uart(WRITE_ACK);
	CommSendTail();
}

//2. r <addr> <count>\r  //read <count> number of value from memory block from <addr>
void _r_func()
{
     int i;
     unsigned long address, value, count;
	address = getnum();
	count = getnum();
	CommRecvTail();
	CommSendHead(STUDIO_ID);
	putc_uart(DATA_START);
	for (i = 0; i < count; i++) {
        	value = MemoryRead32(address);
           puts(xtoa(value));
           puts(" ");
 		address += 4;
	}
     putc_uart(DATA_END);
	CommSendTail();
}

//2. R <count> <addr1> <addr2> ... <addrn>\r  //read <count> number of value from memory block from a series address
void _R_func()
{
     int i;
     unsigned long value, count;
	unsigned long addrvec[100];
	count = getnum();
	for (i = 0; i < count; i++) 
		addrvec[i] = getnum();
	CommRecvTail();
	CommSendHead(STUDIO_ID);
	putc_uart(DATA_START);
	for (i = 0; i < count; i++) {
	     value = MemoryRead32(addrvec[i]);
	     puts(xtoa(value));
	     puts(" ");
	}
	putc_uart(DATA_END);
	CommSendTail();
}

//3. s <addr> <offset> <count> <v1> ... <vn>\r  //write <count> number of values to memory block from the address stored at <addr>
void _s_func()
{
     int i;
     unsigned long address, value, offset, count;
	address = getnum();
	offset = getnum();
	count = getnum();
	CommRecvTail();
	address = MemoryRead32(address) + offset;
	for (i = 0; i < count; i++) {
        	value = getnum();
        	MemoryWrite32(address, value);
 		address += 4;
	}
	CommSendHead(STUDIO_ID);
	putc_uart(WRITE_ACK);
	CommSendTail();
}

//4. l <addr> <offset> <count>\r  //read <count> number of values from memory block from the address stored at <addr>
void _l_func()
{
     int i;
     unsigned long address, value, offset, count;
	address = getnum();
	offset = getnum();
	count = getnum();
	CommRecvTail();
	address = MemoryRead32(address) + offset;
	CommSendHead(STUDIO_ID);
	putc_uart(DATA_START);
	for (i = 0; i < count; i++) {
        	value = MemoryRead32(address);
           puts(xtoa(value));
           puts(" ");
		address += 4;
	}
      putc_uart(DATA_END);
	CommSendTail();
}

//5. j <addr>\r //jump to function at <addr>
void _j_func()
{
     unsigned long address;
     FuncPtr funcPtr;
	address = getnum();
	CommRecvTail();
	CommSendHead(STUDIO_ID);
	putc_uart(WRITE_ACK);
	CommSendTail();
     funcPtr = (FuncPtr)address;
     funcPtr();
}

//6. S <(char)id> //set the port id
void _S_func(/*char msg[], int *index*/)
{
	char ch = getch();
	//charcat(msg, ch);
	if (ch == 'S') {
		//charcat(msg, __mac_id);
		setMAC(getch());
		//ch = getMAC();
		//charcat(msg, ch);
		CommRecvTail();
	}
}

//6. P  //connect probe the port id
void _ProbeConn_func()
{
     	int i = 0;
	CommSendHead(STUDIO_ID);
     	puts("\rstart connecting probe ");
	while (!kbhit()) {
    		probe_setup();
		i++;
		if (i == 1000) 
           	puts(".");
        	else if (i == 100000)
            	break;
     	}
     	puts("\rprobe connected\n");
	CommSendTail();
}

void gdb() 
{
   	int ch;
     for(;;) {
		char port;
		/*int index;
		char msg[DATA_SIZE];
		index = 0;
		msg[0] = 0;*/
		if (!CommRecvHead(&port/*, msg, &index*/)) 						continue;
		ch = getch();
		//charcat(msg, ch);
		switch(ch)
		{              
			case 'w':
		 		_w_func();
                 	break;
             	case 'r':
		 		_r_func();
                 	break;
	     		case 'R':
	     	 		_R_func();
	     	 		break;
             	case 's':
		 		_s_func();
                 	break;
            	case 'l':
		 		_l_func();
                 	break;
            	case 'j':    // jump to address (user input)
		 		_j_func();
                 	break;
			case 'S':    
				_S_func(/*msg, &index*/);
				break;
			case 'P':
				_ProbeConn_func();
				break;
            	case 'g': 
				CommRecvTail();
				return;
		}
		/*CommSendHead2(STUDIO_ID, BROADCAST_ID);
		charcat(msg, '\r');
		puts(msg);
		CommSendTail();*/
	} // for
}

void interrupt(void)
{
	//first check debug enable is on or not
	long value = MemoryRead32(SYS_IRQ_REG);
	long uart0_flag = value & 0x1;
	long dbg_flag = value & 0x10;
	int ch = read_uart();
	/*puts(xtoa(uart0_flag));
	puts(" dbg ");
	puts(xtoa(dbg_flag));
	puts(" ");
	puts(xtoa(ch));*/
	if (dbg_flag == 0) {  //breakpoint not reached, check interrupt
		if (uart0_flag > 0) {		
			if (ch == 0x6) //interrupt button pushed
				dbg_flag = 1;
		}
	}
	if (/*uart0_flag > 0 || */dbg_flag > 0) { //debugger is on, uart0_flag is 1 when debugger called interrupt by Ctrl_C
		CommSendHead(STUDIO_ID);
		putc_uart(DBG_ACK); //acknowledge debugger is reached
		CommSendTail();
	  	gdb();
	} else { //go to handler @0x10000008
	  	MemoryWrite(USER_INT, 0x1);
		user_interrupt();
	}
}

