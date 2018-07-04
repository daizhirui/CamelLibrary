/**
* @file analogIO.c
* @author Zhirui Dai
* @date 15 Jun 2018
* @copyright 2018 Zhirui
* @brief Analog Input Output Library for M2
*/
#include "analogIO.h"
#include "TC0.h"
#include "mcu.h"

inline void RT_ADC_Clear()
{
    MemoryWrite32(AD_CLR_REG, 1);
}

inline void RT_ADC_V2P_On()
{
     MemoryOr32(AD_CTL0_REG, (1 << 8));
}

inline void RT_ADC_V2P_Off()
{
    MemoryAnd32(AD_CTL0_REG, ~(1 << 8));
}

inline void RT_ADC_TemperatureSensorOn()
{
    MemoryOr32(AD_CTL0_REG, 1 << 5);
}

inline void RT_ADC_TemperatureSensorOff()
{
    MemoryAnd32(AD_CTL0_REG, ~(1 << 5));
}

inline void RT_OPO_On()
{
    MemoryOr32(AD_OPO_REG, 0x1);
}

inline void RT_OPO_Off()
{
    MemoryAnd32(AD_OPO_REG, ~0x1);
}

inline void RT_ADC_SD_On(void)
{
    MemoryOr32(AD_CTL0_REG, 1);
}
inline void RT_ADC_SD_Off(void)
{
    MemoryAnd32(AD_CTL0_REG, ~1);
}
inline void RT_ADC_SD_Start()
{
    MemoryWrite32(AD_READ_REG, 1);
}

inline uint32_t RT_ADC_SD_DataReady()
{
    return ((MemoryRead32(AD_CTL0_REG) & 0x80000000) >> 31);
}

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
