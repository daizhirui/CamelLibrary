/**
* @file root_bootloader_io.h
* @author Zhirui Dai
* @date 30 May 2018
* @copyright 2018 Zhirui
* @brief Root Bootloader Input Output
*/

#include "root_bootloader_mcu.h"

#ifndef __ROOT_BOOTLOADER_IO_H__
#define __ROOT_BOOTLOADER_IO_H__

// output a character to uart0
void putchar(char c)
{
    while(MemoryRead32(UART0_BUSY_REG)) {}
    MemoryWrite32(UART0_WRITE_REG, c);
}

void u1_putchar(char c)
{
    while (MemoryRead32(UART1_BUSY_REG)) {}
    MemoryWrite32(UART1_WRITE_REG, c);
}

// output a string to uart0
void puts(const char* string)
{
   while(*string) {
      if(*string == '\n')
         putchar('\r');
      putchar(*string++);
  } // End of while
}

void u1_puts(const char* string)
{
    while(*string) {
       if(*string == '\n')
          u1_putchar('\r');
       u1_putchar(*string++);
   } // End of while
}

#define uart0_data_ready()    MemoryRead32(UART0_DATA_RDY_REG)
#define uart0_read()          (MemoryRead32(UART0_READ_REG)&0xff)

unsigned char getchar()
{
    while(!uart0_data_ready()) {}
    return (unsigned char)uart0_read();
}

#define uart1_data_ready()  MemoryRead32(UART1_DATA_RDY_REG)
#define uart1_read()        (MemoryRead32(UART1_READ_REG)&0xff)

unsigned char u1_getchar()
{
    while (!uart1_data_ready()) {}
    return (unsigned char)uart1_read();
}

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
      ch  = getchar();
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

unsigned long u1_getnum()
{
   int i;
   unsigned char ch;
   unsigned long value=0;

   for(i = 0; i < 16; )   // why 16 ? not 8?
   {
      ch  = u1_getchar();
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

// print hardware information
void print_hdr()
{
        MemoryWrite(SYS_GDR_REG, 0x1450000); // [24:16]=0x145 == uart-bit num
        putchar(0x0a);
        putchar(0x0d);
        puts("\r\n-- Bootloader V1.1  2017-04-15 --\r\n");
        putchar(0x0a);
        putchar(0x0d);
}

// print menu
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

void print_menu1()
{
        u1_puts("\r\n Menu-0001-: \r\n");
        u1_puts("1. Memory write word\r\n");
        u1_puts("2. Memory read word\r\n");
        u1_puts("3. Jump to address -- i.g.: 0x10000000\r\n");
        u1_puts("4. Dump from address\r\n");
        u1_puts("> ");
}

#endif // End of __ROOT_BOOTLOADER_IO_H__
