/**
* @file root_bootloader.c
* @author Zhirui Dai
* @date 30 May 2018
* @copyright 2018 Zhirui
* @brief Root Bootloader for M2
*/


#include "root_bootloader_mcu.h"
#include "root_bootloader_init.h"
#include "root_bootloader_io.h"
#include "root_bootloader_studio.h"

#define USER_SPACE_TEST 0   // 1=Run in root space, 0=Run in user space.
#define PRINT_DEBUG     0   // 1=Print debug message.

void interrupt(void)
{
    FuncPtr funcPtr;
    funcPtr = (FuncPtr)0x10000008;
    funcPtr();
}

int studio_main(int type)
{
    int ch;

    sys_init();
    if (type == 1)  _Uart_sync();
    print_menu();       // print the menu for studio

    for(;;){
        ch = getchar();
        switch(ch){
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
    MemoryWrite32(0x1f800702,0x00001000); // set baudrate to 19200
    int i, k, ch;
    unsigned long address, address1,value, count, v;
    FuncPtr funcPtr;

	address = 0;
	address1 = 0;
	value = 0;
	count = 0;
	v = 0;
    // init
    print_hdr();
    // main loop
    for(;;) {
        print_menu();
        puts("v1.0 hello> ");
        ch = getchar();

        if ('1' <= ch && ch <= '9') {
            MemoryWrite(UART0_IRQ_ACK_REG,  0x1);      // Uart irq clear
            puts("\nAddress in hex> ");
            address = getnum();
            puts("Address = ");
            puts(xtoa(address));
            putchar('\n');
        }

        switch(ch) {
            case '1':{  //
                puts("\nValue in hex> ");
                value = getnum();
                puts(xtoa(value));
                MemoryWrite32(address, value);
                break;
            }

            case '2':{
                value = MemoryRead32(address);
                puts(xtoa(value));
                puts("\r\n");
                break;
            }

            case '3':{    // jump to address (user input)
                funcPtr = (FuncPtr)address;
                funcPtr();
                break;
            }

            case '4':{    // dump to
                puts("\nCount in hex> ");
                count = getnum();
                value = 0;
                for(i = 0; i < count; i += 4)
                {
                if((i & 15) == 0)
                puts("\r\n");
                value = *(unsigned long*)(address+i);
                puts(xtoa(value));
                putchar(' ');
                }
                puts("\r\n");
                break;
            }

            case '5':{    // raw test.bin file
                puts("\nGreetings from the bootloader ");
                puts(__DATE__);
                puts(" ");
                puts(__TIME__);
                puts(":\n");
                puts("\nWaiting for binary image linked at ");
                puts(xtoa(address));
                puts("\n");
                /*
                * max 1k tram space for inst loading
                * now increased to 2kx8 for sejoy flash size user code 16kx32
                * the new sejoy code size = 32kx32, meaning there will be 32k lines
                * the i = 32kx4 (byte addressable) = 2kx64
                */
                unsigned int timeout = 100000;
                unsigned char start = 0;
                start = 0;
                while (!start) {                                    // Block to wait for the beginning of uploading.
                    start = uart0_data_ready();
                }
                start = 1;                                          // Uploading starts!
                for(i = 0; i < 2048*64&&timeout; i=i+4) {           // Flash volume is 128k-byte.
                    value = 0;                                      // Initialize value.
                    for (k = 0; k < 4&&timeout; k++) {              // Receive 4-byte instruction code.
                        timeout = 1000;                             // Initialize timeout.
                        while(timeout) {
                            if(uart0_data_ready()||start) {       // If start=1, uart0_data_ready now is 0.
                                start = 0;
                                break;
                            } else {
                                #if PRINT_DEBUG
                                    putchar('-');
                                #endif
                                timeout--;
                            }
                        }
                        #if PRINT_DEBUG
                            puts("Read\n");
                        #endif
                        ch = uart0_read();
                        value = (ch << 24) + (value >> 8);
                    }

                    address1 = address + i;
                    #if PRINT_DEBUG
                        puts("Write to flash.\n");
                    #endif
                    #if USER_SPACE_TEST
                        flashWrite(value, address1);
                    #else
                        MemoryWrite32(address1, value);
                    #endif
                }

                puts("\r\n binary final address= \r\n");
                puts(xtoa(address1));
                puts("\r\n binary final index= \r\n");
                puts(xtoa(i));
                puts("\r\n binary final timeout= \r\n");
                puts(xtoa(timeout));
                // puts("\r\n p2 sending done \r\n");
                // puts(xtoa(address));
                // puts("\r\n p2 j= \r\n");
                // puts(xtoa(j));
                break;
            }

            case '6':        // loop read
                for (;;) {
                value = MemoryRead32(address);
                puts(xtoa(value));
                puts("\r\n");
                if(uart0_data_ready()) break; // exit when any byte is received.
                }
                break;

            case '7': {     // loop write
                puts("\nValue in hex> ");
                value = getnum();
                puts(xtoa(value));
                for (;;) {
                    #if USER_SPACE_TEST
                        flashWrite(value, address);
                    #else
                        MemoryWrite32(address, value);
                    #endif
                    if(uart0_data_ready()) break;
                }
                break;
            }

            case '8':    // dump in 32-bit/line format
                puts("\nCount in hex> ");
                count = getnum();
                value = 0;
                for(i = 0; i < count; i++) {
                    puts("\r\n");
                    value = *(unsigned long*)(address+i);
                    puts(xtoa(value));
                }
                puts("\r\n");
                break;
            #if USER_SPACE_TEST
                case '9':
                    JumpTo(0x0);
                    break;
            #endif
            } // case
    } // for
    return 0;
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
            ch = u1_getchar();

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
                        u1_putchar(' ');
                }
                u1_puts("\r\n");
                break;

            } // case
    }   // for

    return 0;
}
