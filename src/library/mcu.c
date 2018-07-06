/**
* @file mcu.c
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief M2 micro core unit
*/

#include "mcu.h"

inline void RT_MCU_JumpTo(unsigned long address)
{
    FuncPtr funcptr;
    funcptr = (FuncPtr)address;
    funcptr();
}

inline void RT_MCU_SetSystemClock(uint32_t mode)
{
    MemoryAnd32(SYS_CTL2_REG, ~SYS_CLK_12M);
    MemoryOr32(SYS_CTL2_REG, mode);
}

// clear the sram
void RT_Sram_Clear()
{
    unsigned long i;
    for(i=0;i<7168;i++)
    {
      (*(volatile unsigned char *)(0x01000000 + i)) = 0;
    }
}
