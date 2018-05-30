//################################################################
// TITLE: Mini Boot Loader - m2-sejoy
// AUTHOR: John & Matt
// DATE CREATED: 12/10/2013
// FILENAME: minib.c
// PROJECT: m2-sejoy
// COPYRIGHT: Copyright (C) Camel Microelectronics, Inc.
// DESCRIPTION:
// Rev No.: V1.9
//
//   Mini Boot Loader resides @0        (2kx32 rom)
//
//  03/02/2018 - bill - V1.10 - add p1_main for dual core
//  08/20/2015 - john - V1.9 - added EF write in mybt.s, for m2c
//  06/02/2014 - john - V1.8 - print_sysctl, clean up, and put rev, mode infor
//  04/27/2014 - john - V1.7 - remove print_gdr in interrupt(); make it release version
//  03/27/2014 - matt - B1.6 - T3 -> T2, max line of loader increased
//                             to 32k lines (to fit sejoy)
//  02/26/2014 - john - B1.5 - remove explicit uart print functions
//  01/24/2014 - matt - B1.3 - more dbg msg added for loader part
//                             load file size up to 16k lines (flash size)
//  01/22/2014 - matt - B1.2 - file transfer modification
//                           - added write loop and read loop for testing
//  12/10/2013 - john - B1.1 - based on m1 minib.c, porting to m2 sejoy
//                             use m2.h
//
//################################################################

#include "mcu.h"
//#include "str.h"
//#include "helper.h"

typedef void (*FuncPtr)(void);


//#define DEBUG //For RTL Simulation USE



//
// top menu
//
void print_menu0()
{
        puts("\r\n Menu-0000-: \r\n");
        puts("a. CamelStudio Console\r\n");
        puts("b. CamelStudio Console With Sync\r\n");
        puts("-----------\r\n");
        puts("1. Memory write word\r\n");
        puts("2. Memory read word\r\n");
        puts("3. Jump to address -- i.g.: 0x10000000\r\n");
        puts("4. Dump from address\r\n");
        puts("5. Bootloader\r\n");
        puts("6. Memory loop read word\r\n");
        puts("7. Memory loop write word\r\n");
        puts("8. Dump word from address\r\n");
        puts("> ");
}

void print_hdr()
{
        MemoryWrite(SYS_GDR_REG, 0x1450000); // [24:16]=0x145 == uart-bit num
        putch(0x0a);
        putch(0x0d);
        puts("\r\n-- Bootloader V1.1  2017-04-15 --\r\n");
        putch(0x0a);
        putch(0x0d);
}

int studio_main(int type)
{
    int ch;

    sys_init();
    if (type == 1)
            _Uart_sync();
    print_menu();

    for(;;)
    {
            ch = getch();

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

            case 'j': // jump to address (user input)
                    _j_func();
                    break;

            } // case
    }   // for

    return 0;
}


int main(void)
{
    int i, j, k, ch;
    unsigned long address, address1,value, count, v;
    FuncPtr funcPtr;
    address = 0;
    address1 = 0;
    value = 0;
    count = 0;
    v = 0;

    //
    // init
    //
    sys_init();
    print_hdr();

    for(;;) {
            print_menu0();
            puts("v1.0 hello> ");
            ch = getch();

            if ('1' <= ch && ch <= '9')
            {
                    MemoryWrite(UART0_IRQ_ACK_REG,  0x1);// Uart irq clear
                    puts("\nAddress in hex> ");
                    address = getnum();
                    puts("Address = ");
                    puts(xtoa(address));
                    puts("\n");
            }

            switch(ch) {
            case 'a':
                    studio_main(0);
                    break;
            case 'b':
                    studio_main(1);
                    break;
            case '1': {
                    puts("\nValue in hex> ");
                    value = getnum();
                    puts(xtoa(value));
                    MemoryWrite32(address, value);
                    break;
            }

            case '2': {
                    value = MemoryRead32(address);
                    puts(xtoa(value));
                    puts("\r\n");
                    break;
            }

            case '3': { // jump to address (user input)
                    funcPtr = (FuncPtr)address;
                    funcPtr();
                    break;
            }

            case '4': { // dump to
                    puts("\nCount in hex> ");
                    count = getnum();
                    value = 0;
                    for(i = 0; i < count; i += 4)
                    {
                            if((i & 15) == 0)
                                    puts("\r\n");
                            value = *(unsigned long*)(address+i);
                            puts(xtoa(value));
                            putc_uart(' ');
                    }
                    puts("\r\n");
                    break;
            }

            case '5': { // raw test.bin file
                    puts("\nGreetings from the bootloader ");
                    puts(__DATE__);
                    puts(" ");
                    puts(__TIME__);
                    puts(":\n");
                    puts("\nWaiting for binary image linked at ");
                    puts(xtoa(address));
                    puts("\n");

                    //                 ptr1 = (unsigned long*)0x10000000;
                    /*
                     * max 1k tram space for inst loading
                     * now increased to 2kx8 for sejoy flash size user code 16kx32
                     * the new sejoy code size = 32kx32, meaning there will be 32k lines
                     * the i = 32kx4 (byte addressable) = 2kx64
                     */
                    //                 for(i = 0; i < 2048*8; i=i+4)
                    unsigned int timeout = 1000000;
                    while(timeout) {
                            for (i=0; i<131072&&timeout; i+=4) {
                                    value = 0; v=0;
                                    for (k=0; k<4&&timeout; ) {
                                            if (kbhit()) {
                                                    ch = MemoryRead32(0x1f800000);
                                                    value = (ch << 24) + (value>>8);
                                                    k++;
                                            } else {
                                                    timeout--;
                                            }
                                    }
                                    address1 = address + i;
                                    MemoryWrite32(address1, value);
                            }
                    }
            }
                    //             for(i = 0; i < 2048*64; i=i+4)
                    //             {
                    //             value = 0; v=0;
                    //             for (k = 0; k < 4; k++)
                    //             {
                    //                 ch = getch();
                    //                 v = ch << 24;
                    //                 value = v + (value >> 8);
                    // //                      value = (value << 8) + ch;    // each line is a long value
                    // //                      value = value +  (ch << 8*k);    // each line is a long value
                    //             }

                    //             address1 = address + i;
                    //             MemoryWrite32(address1, value);
                    //             /*
                    //                 * this is to test end of file
                    //                 * not sure if it works
                    //                 */
                    //             for(j = 0; j < 10000; ++j)
                    //             {
                    //                 if(kbhit())
                    //                 break;
                    //             }
                    //             if(j >= 10000)
                    //                 break;       //assume end of file
                    //             }
                    puts("\r\n p1 final address= \r\n");
                    puts(xtoa(address1));
                    puts("\r\n p1 final index= \r\n");
                    puts(xtoa(i));
                    puts("\r\n p1 final j= \r\n");
                    puts(xtoa(j));

                    for(i = 0; i < 1024*1024; i++)
                    {
                            for(j = 0; j < 10000; ++j)
                            {
                                    if(kbhit())
                                            break;
                            }
                            if(j >= 10000)
                                    break; //assume end of file

                            ch = getch();
                    }
                    puts("\r\n p2 sending done \r\n");
                    puts(xtoa(address));
                    puts("\r\n p2 j= \r\n");
                    puts(xtoa(j));

                    break;

            case '6':    // loop read
                    for (;;) {
                            value = MemoryRead32(address);
                            puts(xtoa(value));
                            puts("\r\n");

                            if(kbhit())
                                    break;
                    }
                    break;

            case '7':
                    puts("\nValue in hex> ");
                    value = getnum();
                    puts(xtoa(value));
                    for (;;) {
                            MemoryWrite32(address, value);
                            if(kbhit())
                                    break;
                    }
                    break;

            case '8': // dump in 32-bit/line format
                    puts("\nCount in hex> ");
                    count = getnum();
                    value = 0;
                    for(i = 0; i < count; i++)
                    {
                            puts("\r\n");
                            value = *(unsigned long*)(address+i);
                            puts(xtoa(value));
                    }
                    puts("\r\n");
                    break;
            } // case
    } // for

    return 0;
}

void print_menu1()
{
        u1_puts("\r\n Menu-0001-: \r\n");
        u1_puts("1. Memory write word\r\n");
        u1_puts("2. Memory read word\r\n");
        u1_puts("3. Jump to address -- i.g.: 0x10000000\r\n");
        u1_puts("4. Dump from address\r\n");
        u1_puts("> ");
}

int p1_main(void)
{
        int i, ch;
        unsigned long address, value, count;
        FuncPtr funcPtr;
        address = 0;
        value = 0;
        count = 0;

        for(;;)
        {
                print_menu1();
                u1_puts("v1.0 hello> ");
                ch = u1_getch();

                if ('1' <= ch && ch <= '9')
                {
                        MemoryWrite(UART1_IRQ_ACK_REG,  0x1);// Uart irq clear
                        u1_puts("\nAddress in hex> ");
                        address = u1_getnum();
                        u1_puts("Address = ");
                        u1_puts(xtoa(address));
                        u1_puts("\n");
                }

                switch(ch)
                {
                case '1':
                        u1_puts("\nValue in hex> ");
                        value = u1_getnum();
                        u1_puts(xtoa(value));
                        MemoryWrite32(address, value);
                        break;
                case '2':
                        value = MemoryRead32(address);
                        u1_puts(xtoa(value));
                        u1_puts("\r\n");
                        break;

                case '3': // jump to address (user input)
                        funcPtr = (FuncPtr)address;
                        funcPtr();
                        break;

                case '4': // dump to
                        u1_puts("\nCount in hex> ");
                        count = u1_getnum();
                        value = 0;
                        for(i = 0; i < count; i += 4)
                        {
                                if((i & 15) == 0)
                                        u1_puts("\r\n");
                                value = *(unsigned long*)(address+i);
                                u1_puts(xtoa(value));
                                u1_putc_uart(' ');
                        }
                        u1_puts("\r\n");
                        break;

                } // case
        }   // for

        return 0;
}
