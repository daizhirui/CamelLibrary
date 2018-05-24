/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: John & Jack 
 * DATE CREATED: 2017/11/4
 * FILENAME: CORE.h
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 * 		This file is copied from V20170715 directly.
 *--------------------------------------------------------------------*/
#include "CORE.h"
#include "mcu.h"
/**
 * @brief 
 * This function is a time delay function
 * @param ms    the time to delay, the unit is ms
 * @return      void
 */
void RT_Delay_ms(unsigned long ms)
{	
	unsigned int i;
	while(ms--)
	{
		for (i = 0; i < 200; i++)
			asm("nop");
	}
}
/**
 * @brief 
 * This function is to clear the sram
 * @return void
 */
void RT_Clr_Ram()  
{
    unsigned long i;
    for(i=0;i<2048;i++)
    {
      (*(volatile unsigned char *)(0x01000000 + i)) = 0; 
    }
}
