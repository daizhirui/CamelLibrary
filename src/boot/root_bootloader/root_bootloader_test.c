/**
* @file root_bootloader_test.c
* @author Zhirui Dai
* @date 30 May 2018
* @copyright 2018 Zhirui
* @brief Root Bootloader Test
*/

#include "root_bootloader_mcu.h"
#include "root_bootloader_io.h"

#define USER_SPACE_TEST 1
#define PRINT_DEBUG     0

typedef void (*FuncPtr)(void);

//#define DEBUG //For RTL Simulation USE

void user_interrupt(){}

void print_hardware()
{
    MemoryWrite(SYS_GDR_REG, 0x1450000); // [24:16]=0x145 == uart-bit num
    putchar(0x0a);
    putchar(0x0d);
    puts("\r\n-- Bootloader V2.1  2018-05-29 --\r\n");
    putchar(0x0a);
    putchar(0x0d);
}

void print_menu()
{
    puts("\r\n Menu-0000-: \r\n");
    puts("1. Memory write word\r\n");
    puts("2. Memory read word\r\n");
    puts("3. Jump to address -- i.g.: 0x10000000\r\n");
    puts("4. Dump from address\r\n");
    puts("5. Bootloader\r\n");
    puts("6. Memory loop read word\r\n");
    puts("7. Memory loop write word\r\n");
    #if USER_SPACE_TEST
        puts("8. Erase flash from address\r\n");
        puts("9. Go to root space\r\n");
    #endif
    puts("> ");
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
    print_hardware();
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
                #if USER_SPACE_TEST
                    flashWrite(value,address);
                #else
                    MemoryWrite32(address, value);
                #endif
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
            #if USER_SPACE_TEST
            case '8':    // dump in 32-bit/line format
                puts("\r\nFlash erase from ");puts(xtoa(address));puts("\r\n");
                address = 0x10100000|(address&0x1ffff);
                for(;address<0x1011fff0;address+=0x400) {
                    puts("flashErase: ");
                    puts(xtoa(address));
                    puts("\r\n");
                    flashErase(address);
                    putchar('.');
                }
                puts("Completed!\r\n");
                break;
                case '9':
                    JumpTo(0x0);
                    break;
            #endif
            } // case
    } // for
    return 0;
}
