/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/2
 * FILENAME: AFE.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 * 		Analog Module Library
 * 		2017/11/3	updated from V2017.07.15
 *--------------------------------------------------------------------*/
#include "mcu.h"
#include "TC0.h"
#include "AFE.h"
#include "time.h"
/**
 * @brief 
 * This function is used to get the value of ADC_SD.
 * @return int 		ADC_SD result
 */
int RT_ADC_SD_Read()
{	
	register int i;
	MemoryWrite32(AD_CLR_REG, 0); 			   //clear ADC to prepare reading
	for (i = 0; i < 200; i++)
		asm("nop");							   //add delay for acc_en up
	if (!(MemoryRead32(AD_CTL0_REG) >> 6) & 1) // use SD_WT2READ as trigger source
		RT_ADC_SD_Start();						   //kick off the ADC read process
	while (!(MemoryRead32(AD_CTL0_REG) & 0x80000000))
		;										//check if rdy bit is ok
	return MemoryRead32(AD_READ_REG) & 0x3ffff; //read the low 18bit data
} // End of ADC_SD_Read

/**
 * @brief 
 * This function is used to get the value of ADC_V2P.
 * @return int 		ADC_V2P result
 */
int RT_ADC_V2P_Read()
{
	int count = 0;
	int number = 16; //16 times to average
	int valid = 0;
	int i = 0;
	for (i = 0; i < number; i++)
	{
		int tmp;
		RT_TC0_ClearAll();
		while (!RT_TC0_CheckTcFlag())
			;
		tmp = RT_TC0_ReadCnt();
		if (tmp > 1000)
		{
			valid++;
			count += tmp;
		}
	}
	if (valid > 0)
		return count / valid;
	else
		return 0;
} // End of ADC_V2P_Read