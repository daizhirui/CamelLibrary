/**
 * @brief M2 micro core unit
 * 
 * @file mcu.h
 * @author Zhirui Dai
 * @date 2018-05-25
 */

#include "mcu.h"

/**
 * @brief 
 * This function is to clear the sram
 * @return void
 */
void RT_Clr_Sram()
{
    unsigned long i;
    for(i=0;i<2048;i++)
    {
      (*(volatile unsigned char *)(0x01000000 + i)) = 0; 
    }
}
