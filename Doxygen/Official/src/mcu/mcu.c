/**
* @file mcu.c
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief M2 micro core unit
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
