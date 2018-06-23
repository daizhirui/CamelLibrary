/**
* @file Flash.h
* @author Zhirui Dai
* @date 22 Jun 2018
* @copyright 2018 Zhirui
* @brief Flash Operation Library for M2
*/

#ifndef __M2_FLASH_H__
#define __M2_FLASH_H__

#include "mcu.h"

/*! \cond PRIVATE */
#define FLASH_WRITE_ADDRESS 0x2c4
#define FLASH_ERASE_ADDRESS 0x2f8
/*! \endcond */

#define RT_Flash_Write(value, address)                  \
    {                                                   \
        FuncPtr2 funcptr;                               \
        funcptr = (FuncPtr2)FLASH_WRITE_ADDRESS;        \
        uint32_t oldVal = MemoryRead32(SYS_CTL2_REG);   \
        RT_MCU_SetSystemClock(SYS_CLK_6M);              \
        funcptr(value, address);                        \
        MemoryWrite32(SYS_CTL2_REG, oldVal);            \
    }

#define RT_Flash_Erase1k(address)                       \
    {                                                   \
        unsigned long addr;                             \
        FuncPtr1 funcptr;                               \
        funcptr =  (FuncPtr1)FLASH_ERASE_ADDRESS;       \
        addr = ((address&0x1ffff) | 0x10100000);        \
        uint32_t oldVal = MemoryRead32(SYS_CTL2_REG);   \
        RT_MCU_SetSystemClock(SYS_CLK_6M);              \
        funcptr(addr);                                  \
        MemoryWrite32(SYS_CTL2_REG, oldVal);            \
    }

#define RT_Flash_EraseFrom(address)                                     \
    {                                                                   \
        for(unsigned long addr=address;addr<0x10001f400;addr+=0x400) {  \
            RT_Flash_Erase1k(addr);                                     \
        }                                                               \
    }

// MAC_ID address.
#define MAC_ID 0x1001f3f0

/**
 * @brief Set chip identity(MAC_ID).
 */
#define RT_Flash_SetMAC(id)     RT_Flash_Write(id, MAC_ID)

/**
 * @brief Get chip identity(MAC_ID).
 */
#define getMAC() MemoryRead32(MAC_ID)

#endif
