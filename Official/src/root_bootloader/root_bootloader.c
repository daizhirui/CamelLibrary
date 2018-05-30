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
#include "UART0.h"

#define USER_SPACE_TEST 1
#define PRINT_DEBUG     0

typedef void (*FuncPtr)(void);

//#define DEBUG //For RTL Simulation USE

void user_interrupt(){}

char* xtoa(unsigned long num)
{
   static char buf[12];
   int i, digit;
   buf[8] = 0;
   for (i = 7; i >= 0; --i) {
      digit = num & 0xf;
      buf[i] = digit + (digit < 10 ? '0' : 'A' - 10);
      num >>= 4;
  } // End of for
   return buf;
}

unsigned long getnum()
{
   int i;
   unsigned char ch;
   unsigned long value=0;

   for(i = 0; i < 16; )   // why 16 ? not 8?
   {
      ch  = RT_UART0_getchar();
      if(ch == '\r')
         break;
      if(ch == '\n' || ch == '\r' || ch == ' ')
         break;
      if('0' <= ch && ch <= '9')
         ch -= '0';
      else if('A' <= ch && ch <= 'Z')
         ch = ch - 'A' + 10;
      else if('a' <= ch && ch <= 'z')
         ch = ch - 'a' + 10;
      else if(ch == 8)  // \b  backspace
      {
         if(i > 0)
            --i;
         value >>= 4;
         continue;
      }
      value = (value << 4) + ch;
      ++i;
   }
   return value;
}

void print_hardware()
{
    MemoryWrite(SYS_GDR_REG, 0x1450000); // [24:16]=0x145 == uart-bit num
    RT_UART0_putchar(0x0a);
    RT_UART0_putchar(0x0d);
    RT_UART0_puts("\r\n-- Bootloader V1.1  2018-05-29 --\r\n");
    RT_UART0_putchar(0x0a);
    RT_UART0_putchar(0x0d);
}

void print_menu()
{
    RT_UART0_puts("\r\n Menu-0000-: \r\n");
    RT_UART0_puts("1. Memory write word\r\n");
    RT_UART0_puts("2. Memory read word\r\n");
    RT_UART0_puts("3. Jump to address -- i.g.: 0x10000000\r\n");
    RT_UART0_puts("4. Dump from address\r\n");
    RT_UART0_puts("5. Bootloader\r\n");
    RT_UART0_puts("6. Memory loop read word\r\n");
    RT_UART0_puts("7. Memory loop write word\r\n");
    RT_UART0_puts("8. Dump word from address\r\n");
    #if USER_SPACE_TEST
        RT_UART0_puts("9. Go to root space\r\n");
    #endif
    RT_UART0_puts("> ");
}

int main(void)
{
    MemoryWrite32(0x1f800702,0x00001000); // set baudrate to 19200
    int i, j, k, ch;
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
        RT_UART0_puts("v1.0 hello> ");
        ch = RT_UART0_getchar();

        if ('1' <= ch && ch <= '9') {
            MemoryWrite(UART0_IRQ_ACK_REG,  0x1);      // Uart irq clear
            RT_UART0_puts("\nAddress in hex> ");
            address = getnum();
            RT_UART0_puts("Address = ");
            RT_UART0_puts(xtoa(address));
            RT_UART0_putchar('\n');
        }

        switch(ch) {
            case '1':{  //
                RT_UART0_puts("\nValue in hex> ");
                value = getnum();
                RT_UART0_puts(xtoa(value));
                MemoryWrite32(address, value);
                break;
            }

            case '2':{
                value = MemoryRead32(address);
                RT_UART0_puts(xtoa(value));
                RT_UART0_puts("\r\n");
                break;
            }

            case '3':{    // jump to address (user input)
                funcPtr = (FuncPtr)address;
                funcPtr();
                break;
            }

            case '4':{    // dump to
                RT_UART0_puts("\nCount in hex> ");
                count = getnum();
                value = 0;
                for(i = 0; i < count; i += 4)
                {
                if((i & 15) == 0)
                RT_UART0_puts("\r\n");
                value = *(unsigned long*)(address+i);
                RT_UART0_puts(xtoa(value));
                RT_UART0_putchar(' ');
                }
                RT_UART0_puts("\r\n");
                break;
            }

            case '5':{    // raw test.bin file
                RT_UART0_puts("\nGreetings from the bootloader ");
                RT_UART0_puts(__DATE__);
                RT_UART0_puts(" ");
                RT_UART0_puts(__TIME__);
                RT_UART0_puts(":\n");
                RT_UART0_puts("\nWaiting for binary image linked at ");
                RT_UART0_puts(xtoa(address));
                RT_UART0_puts("\n");
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
                    start = RT_UART0_DataReady();
                }
                start = 1;                                          // Uploading starts!
                for(i = 0; i < 2048*64&&timeout; i=i+4) {           // Flash volume is 128k-byte.
                    value = 0;                                      // Initialize value.
                    for (k = 0; k < 4&&timeout; k++) {              // Receive 4-byte instruction code.
                        timeout = 1000;                             // Initialize timeout.
                        while(timeout) {
                            if(RT_UART0_DataReady()||start) {       // If start=1, RT_UART0_DataReady now is 0.
                                start = 0;
                                break;
                            } else {
                                #if PRINT_DEBUG
                                    RT_UART0_putchar('-');
                                #endif
                                timeout--;
                            }
                        }
                        #if PRINT_DEBUG
                            RT_UART0_puts("Read\n");
                        #endif
                        ch = RT_UART0_Read();
                        value = (ch << 24) + (value >> 8);
                    }

                    address1 = address + i;
                    #if PRINT_DEBUG
                        RT_UART0_puts("Write to flash.\n");
                    #endif
                    #if USER_SPACE_TEST
                        flashWrite(value, address1);
                    #else
                        MemoryWrite32(address1, value);
                    #endif
                }

                RT_UART0_puts("\r\n binary final address= \r\n");
                RT_UART0_puts(xtoa(address1));
                RT_UART0_puts("\r\n binary final index= \r\n");
                RT_UART0_puts(xtoa(i));
                RT_UART0_puts("\r\n binary final timeout= \r\n");
                RT_UART0_puts(xtoa(timeout));
                RT_UART0_puts("\r\n p2 sending done \r\n");
                RT_UART0_puts(xtoa(address));
                RT_UART0_puts("\r\n p2 j= \r\n");
                RT_UART0_puts(xtoa(j));

                break;
            }

            case '6':        // loop read
                for (;;) {
                value = MemoryRead32(address);
                RT_UART0_puts(xtoa(value));
                RT_UART0_puts("\r\n");
                if(RT_UART0_DataReady()) break; // exit when any byte is received.
                }
                break;

            case '7': {     // loop write
                RT_UART0_puts("\nValue in hex> ");
                value = getnum();
                RT_UART0_puts(xtoa(value));
                for (;;) {
                    #if USER_SPACE_TEST
                        flashWrite(value, address);
                    #else
                        MemoryWrite32(address, value);
                    #endif
                    if(RT_UART0_DataReady()) break;
                }
                break;
            }

            case '8':    // dump in 32-bit/line format
                RT_UART0_puts("\nCount in hex> ");
                count = getnum();
                value = 0;
                for(i = 0; i < count; i++) {
                    RT_UART0_puts("\r\n");
                    value = *(unsigned long*)(address+i);
                    RT_UART0_puts(xtoa(value));
                }
                RT_UART0_puts("\r\n");
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
