# Sigma Delta   {#SD}

To use this library, please include `analogIO.h`.

## Interface

```C
void RT_ADC_SD_On();

void RT_ADC_SD_Off();

void RT_ADC_SD_SetSampleRate(mode);

void RT_ADC_SD_SetAdWidth(mode);

void RT_ADC_SD_SetTrigger(source);

void RT_ADC_SD_Setup(sampleRate, adWidth, triggerSource);

void RT_ADC_SD_Start();

uint32_t RT_ADC_SD_DataReady();

uint32_t RT_ADC_SD_Read();

void RT_ADC_Clear();
```

## Example

```C

#include "analogIO.h"

// This example setups SD simply.
void Example_SD_SimpleSst()
{
    RT_ADC_SD_Setup(SD_CLK_3M, SD_20BIT, SD_TRIG_BY_WT2READ);
    // Turning on SD, clearing SD and starting accumulation are all done in RT_ADC_SD_Read
    uint32_t result = RT_ADC_SD_Read();
    // ...
}

// This example reveals more details about SD setup.
void Example_SD_Basic()
{
    RT_ADC_SD_SetSampleRate(SD_CLK_3M);
    RT_ADC_SD_SetAdWidth(SD_20BIT);
    RT_ADC_SD_SetTrigger(SD_TRIG_BY_TC0PWM);
    RT_ADC_Clear();
    RT_ADC_SD_On();
    for (register uint32_t i=0; i<200;i++)
        __asm__("nop");
    RT_ADC_SD_Start();
    while(!RT_ADC_SD_DataReady());
    uint32_t result = MemoryRead32(AD_READ_REG) & 0xfffff;
    // ...
}
```
