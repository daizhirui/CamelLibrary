#include <mcu.h>
#include <stdio.h>

/**
Flash address range: 0x10000000 -- 0x1001ffff
However, 0x1001fff0 to 0x1001ffff should not be changed.
*/

#define TEST_BEGIN_ADDR 0x1001f000
#define TEST_END_ADDR   0x1001f400
#define TEST_ERASE_ADDR ((TEST_BEGIN_ADDR&0x1ffff) | 0x10100000)

void user_interrupt(){}

void main() {
    unsigned long address;
    unsigned long index, value, empty;
    while(1) {
        puts("Start to test:\n");
        MemoryWrite32(0x1f800702,0x00001000); // set baudrate to 19200
        flashErase(TEST_ERASE_ADDR);     // erase 0x1000f000 to 0x1000f3ff
        index = 0;
        for(address=TEST_BEGIN_ADDR;address<TEST_END_ADDR;address+=4) {
            printf("Writing %x\n", address);
            flashWrite(index, address);
            index++;
        }
        //MemoryWrite32(0x1f800702, 0x00000000);  // set baudrate to 9600
        index = 0;
        empty = 0;
        for(address=TEST_BEGIN_ADDR;address<TEST_END_ADDR;address+=4,index++) {
            value = MemoryRead32(address);
            // puts(xtoa(address));
            // putchar('=');
            // puts(xtoa(value));
            printf("0x%x = 0x%x",address, value);
            if(value == index) {
                puts("............PASS.\n");
            } else if (value == 0xFFFFFFFF) {
                puts("......UNPASS.\n");
                empty++;
            } else {
                puts("......UNPASS.\n");
            }
        }
        puts("Data from 0x1001fff0:\n");
        for(address=0x1001fff0;address<0x10020000;address+=4){
            printf("0x%x = 0x%x\n",address, MemoryRead32(address));
        }
        printf("empty count=%d\n", empty);
        puts("TestComplete.Repeat?");
        switch (getchar()) {
            case 'y': continue;
            case 'n':
            default:  JumpTo(0x00000000);
        }
    }
}
