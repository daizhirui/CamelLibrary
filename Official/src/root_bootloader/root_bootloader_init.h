/**
* @file root_bootloader_init.h
* @author Zhirui Dai
* @date 30 May 2018
* @copyright 2018 Zhirui
* @brief Root Bootloader Initialization
*/

<<<<<<< HEAD
#include "root_bootloader_mcu.h"
=======
#include "mcu.h"
>>>>>>> master

#ifndef __ROOT_BOOTLOADER_INIT_H__
#define __ROOT_BOOTLOADER_INIT_H__

void sys_init()
{
        MemoryWrite(SYS_GDR_REG, 0x14500a5);  // u0 bit num init
        MemoryWrite(INT_CTL2_REG, 0xff);      // ex int high enable set
        MemoryWrite(INT_CLR_REG,  0xff);      // ex int clear
        MemoryWrite(INT_CTL0_REG, 0x00);      // ex int DISABLE set
        MemoryWrite(SYS_IOCTL_REG, 0x0000);   // This 16-bit reg is used as menu record pointer
        MemoryWrite(SD_CTL_REG, 0x0);
        MemoryWrite(INT_COUNT, 0x0); //initialize the reg for recording number of interrupts in the path,
                                     //it determines where SP is stored for each interrupt
        MemoryWrite(USER_INT, 0x0);  //initialize the reg to choose gdb() or user interrupt function when interrupt is generated
}

#endif
