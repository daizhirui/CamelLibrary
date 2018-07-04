//################################################################
// TITLE: helper
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

#include "../lib/mcu.h"
#include "../lib/str.h"

#define START 0
#define END 2018
typedef void (*FuncPtr)(void);
/*
   static const unsigned int cntvals[128] = {256,
                                      384, 128,
         192, 320, 448, 64,
           224, 288, 352, 160, 416, 96, 480, 32,
        208, 240, 272, 176, 304, 144, 336, 112, 368, 400, 432, 80, 464, 496, 48, 16,
    216, 232, 200, 248, 264, 184, 280, 296, 168, 312, 328, 152, 344, 360, 136, 376, 392, 120, 408, 424, 104, 440, 456, 88, 472, 72, 488, 56, 504, 40, 24, 8,
    508, 500, 492, 484, 476, 468, 460, 452, 444, 436, 428, 420, 412, 404, 396, 388, 380, 372, 364, 356, 348, 340, 332, 324, 316, 308, 300, 292, 284, 276, 268, 260, 252, 244, 236, 228, 220, 212, 204, 196, 188, 180, 172, 164, 156, 148, 140, 132, 124, 116, 108, 100, 92, 84, 76, 68, 60, 52, 44, 36, 28, 20, 12, 4};
 */

void _Uart_sync()
{
        int start, cnt, end, count;
        unsigned char tmp;
        start = START;
        end = END;
        count = 0;
        while(1) {
                cnt = (start + end)>>1;
                MemoryWrite32(SYS_GDR_REG, cnt<<1);
                MemoryWrite32(UART_FCNT_REG, cnt<<1);
                tmp = getch();
                count++;
                if (tmp == PAC_HEAD) {
                        MemoryWrite32(UART_FCNT_REG, (cnt+(cnt/20))<<1);
                        tmp = getch();
                        count++;
                        if (tmp == PAC_HEAD)  {
                                cnt = cnt + cnt/40;
                                break;
                        } else if (tmp == 0)
                                start = cnt;
                        else
                                end = cnt;
                        MemoryWrite32(UART_FCNT_REG, (cnt-(cnt/20))<<1);
                        tmp = getch();
                        count++;
                        if (tmp == PAC_HEAD) {
                                cnt = cnt - cnt/40;
                                break;
                        } else if  (tmp == 0)
                                start = cnt;
                        else
                                end = cnt;
                } else if (tmp == 0)
                        start = cnt;
                else {
                        if (tmp == 0x81) {
                                start = ((cnt*7)>>3);
                                end = cnt;
                        } else if (tmp == 0xc1) {
                                start = ((cnt*3)>>2);
                                end = ((cnt*7)>>3);
                        } else if (tmp == 0xc0) {
                                start = ((cnt*5)>>3);
                                end = ((cnt*3)>>2);
                        } else if (tmp == 0xe0) {
                                start = ((cnt*5)>>3);
                                end = ((cnt*3)>>2);
                        } else if (tmp == 0xf0) {
                                start = (cnt>>1);
                                end = ((cnt*5)>>3);
                        } else if (tmp == 0xf8) {
                                start = ((cnt*3)>>3);
                                end = (cnt>>1);
                        } else if (tmp == 0xfc) {
                                start = (cnt>>2);
                                end = ((cnt*3)>>3);
                        } else if (tmp == 0xfe) {
                                start = (cnt>>3);
                                end = (cnt>>2);
                        } else
                                end = (cnt>>2);
                }
        }
        MemoryWrite32(SYS_GDR_REG, cnt<<1);
        MemoryWrite32(UART_FCNT_REG, cnt<<1);
        puts("\r trial number: ");
        puts(xtoa(count));
        puts("\rcenter: ");
        puts(xtoa(cnt));
        puts("\rrange: ");
        puts(xtoa(end - start));
        puts("\rUART SYNC DONE!\r");
}

void sys_init()
{
        MemoryWrite(SYS_GDR_REG, 0x14500a5); // u0 bit num init
        MemoryWrite(INT_CTL2_REG, 0xff);    // ex int high enable set
        MemoryWrite(INT_CLR_REG,  0xff);    // ex int clear
        MemoryWrite(INT_CTL0_REG, 0x00);    // ex int DISABLE set
        MemoryWrite(SYS_IOCTL_REG, 0x0000); // This 16-bit reg is used as menu record pointer
        MemoryWrite(SD_CTL_REG, 0x0);
        MemoryWrite(INT_COUNT, 0x0); //initialize the reg for recording number of interrupts in the path,
                                     //it determines where SP is stored for each interrupt
        MemoryWrite(USER_INT, 0x0); //initialize the reg to choose gdb() or user interrupt function when interrupt is generated
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
        putc_uart(WRITE_ACK);
}

//2. r <addr> <count>\r  //read <count> number of value from memory block from <addr>
void _r_func()
{
        int i;
        unsigned long address, value, count;
        address = getnum();
        count = getnum();
        putc_uart(DATA_START);
        for (i = 0; i < count; i++) {
                value = MemoryRead32(address);
                puts(xtoa(value));
                puts(" ");
                address += 4;
        }
        putc_uart(DATA_END);
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
        putc_uart(DATA_START);
        for (i = 0; i < count; i++) {
                value = MemoryRead32(addrvec[i]);
                puts(xtoa(value));
                puts(" ");
        }
        putc_uart(DATA_END);
}

//3. s <addr> <offset> <count> <v1> ... <vn>\r  //write <count> number of values to memory block from the address stored at <addr>
void _s_func()
{
        int i;
        unsigned long address, value, offset, count;
        address = getnum();
        offset = getnum();
        count = getnum();
        address = MemoryRead32(address) + offset;
        for (i = 0; i < count; i++) {
                value = getnum();
                MemoryWrite32(address, value);
                address += 4;
        }
        putc_uart(WRITE_ACK);
}

//4. l <addr> <offset> <count>\r  //read <count> number of values from memory block from the address stored at <addr>
void _l_func()
{
        int i;
        unsigned long address, value, offset, count;
        address = getnum();
        offset = getnum();
        count = getnum();
        address = MemoryRead32(address) + offset;
        putc_uart(DATA_START);
        for (i = 0; i < count; i++) {
                value = MemoryRead32(address);
                puts(xtoa(value));
                puts(" ");
                address += 4;
        }
        putc_uart(DATA_END);
}

//5. j <addr>\r //jump to function at <addr>
void _j_func()
{
        unsigned long address;
        FuncPtr funcPtr;
        address = getnum();
        putc_uart(WRITE_ACK);
        funcPtr = (FuncPtr)address;
        funcPtr();
}

void interrupt(void)
{
        FuncPtr funcPtr;
        funcPtr = (FuncPtr)0x10000008;
        funcPtr();
}

void print_menu(void)
{
        puts("\r##############################\r\n");
        puts("Hello From MCU             \r\n");
        puts("Bootloader Version 1.0     \r\n");
        puts("Camel Microelectronic, Inc.\r\n");
        puts("##############################\r\n");
}
