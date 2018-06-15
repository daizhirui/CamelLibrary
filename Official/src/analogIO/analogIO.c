/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/2
 * FILENAME: AFE.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *         Analog Module Library
 *         2017/11/3    updated from V2017.07.15
 *--------------------------------------------------------------------*/

#include "analogIO.h"
#include "TC0.h"
#include "time.h"

/**
 * @brief  Get the value of ADC_SD.
 * @return uint32_t  the result from SD.
 */
uint32_t RT_ADC_SD_Read()
{
    register uint32_t i;
    RT_ADC_SD_On();                             // make sure sd is on.
    RT_ADC_Clear();                             // clear ADC to prepare reading
    for (i = 0; i < 200; i++)
        __asm__("nop");                         // add delay for acc_en up
    RT_ADC_SD_SetTrigger(SD_TRIG_BY_WT2READ);   // use SD_WT2READ as trigger source
    RT_ADC_SD_Start();                          // start to accumulate
    while (!RT_ADC_SD_DataReady());             // check if rdy bit is ok
    return MemoryRead32(AD_READ_REG) & 0xfffff; // read the low 20bit data
} // End of ADC_SD_Read

/**
 * @brief  Get the value of ADC_V2P.
 * @return uint32_t the result from V2P
 */
uint32_t RT_ADC_V2P_Read()
{
    uint32_t count = 0;
    uint32_t number = 16; //16 times to average
    uint32_t valid = 0;
    uint32_t i = 0;
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
