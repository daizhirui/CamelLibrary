/**
 * @file root_bootloader_studio.h
 * @author Zhirui Dai
 * @date 30 May 2018
 * @copyright 2018 Zhirui
 * @brief Root Bootloader Stduio Communication
 */

#include "root_bootloader_mcu.h"
#include "root_bootloader_io.h"

#ifndef __ROOT_BOOTLOADER_STUDIO_H__
#define __ROOT_BOOTLOADER_STUDIO_H__


#define START 0
#define END 2018

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
            tmp = getchar();
            count++;
            if (tmp == PAC_HEAD) {
                    MemoryWrite32(UART_FCNT_REG, (cnt+(cnt/20))<<1);
                    tmp = getchar();
                    count++;
                    if (tmp == PAC_HEAD)  {
                            cnt = cnt + cnt/40;
                            break;
                    } else if (tmp == 0)
                            start = cnt;
                    else
                            end = cnt;
                    MemoryWrite32(UART_FCNT_REG, (cnt-(cnt/20))<<1);
                    tmp = getchar();
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


void print_menu(void)
{
    puts("\r##############################\r\n");
    puts("Hello From MCU             \r\n");
    puts("Bootloader Version 1.0     \r\n");
    puts("Camel Microelectronic, Inc.\r\n");
    puts("##############################\r\n");
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
    putchar(WRITE_ACK);
}

//2. r <addr> <count>\r  //read <count> number of value from memory block from <addr>
void _r_func()
{
    int i;
    unsigned long address, value, count;
    address = getnum();
    count = getnum();
    putchar(DATA_START);
    for (i = 0; i < count; i++) {
            value = MemoryRead32(address);
            puts(xtoa(value));
            puts(" ");
            address += 4;
    }
    putchar(DATA_END);
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
    putchar(DATA_START);
    for (i = 0; i < count; i++) {
            value = MemoryRead32(addrvec[i]);
            puts(xtoa(value));
            puts(" ");
    }
    putchar(DATA_END);
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
    putchar(WRITE_ACK);
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
    putchar(DATA_START);
    for (i = 0; i < count; i++) {
            value = MemoryRead32(address);
            puts(xtoa(value));
            puts(" ");
            address += 4;
    }
    putchar(DATA_END);
}

//5. j <addr>\r //jump to function at <addr>
void _j_func()
{
    unsigned long address;
    FuncPtr funcPtr;
    address = getnum();
    putchar(WRITE_ACK);
    funcPtr = (FuncPtr)address;
    funcPtr();
}

#endif
