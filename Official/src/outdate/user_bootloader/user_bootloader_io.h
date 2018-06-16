/**
* @file user_bootloader_io.h
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief User boot loader input output module
*/

#include "UART0.h"

#ifndef __USER_BOOT_LOADER_IO_H__
#define __USER_BOOT_LOADER_IO_H__

void putchar(char c)
{
    while(MemoryRead32(UART0_BUSY_REG)) {}
    MemoryWrite32(UART0_WRITE_REG, c);
}

void puts(const char* string)
{
   while(*string) {
      if(*string == '\n')
         putchar('\r');
      putchar(*string++);
  } // End of while
}


#endif
