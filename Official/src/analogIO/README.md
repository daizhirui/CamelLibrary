# Analog Input Output Library for M2

## Analog Digit Converter

```C
void RT_ADC_Clear();
```

## Amplifier (OPO)

```C
void RT_OPO_On();

void RT_OPO_Off();

void RT_OPO_SetChannel(ch0, ch1, ch2, ch3);

void RT_OPO_SetAmplification(Pin, Pgain, Nin, Ngain);

void RT_OPO_SetPsideFeedback(mode);

void RT_OPO_ExchangeChannelPin(switch);

void RT_OPO_SelectChannelPin(pin);

void RT_OPO_SetSingleSideMode(ch0, ch1, ch2, ch3, pin);

void RT_OPO_SetDifferentialMode(ch0, ch1, ch2, ch3, exchange);

void RT_OPO_SetShort(mode);

void RT_OPO_SetBypass(mode);

void RT_OPO_SetVPGND(op);
```

### Example

```C
#include "analogIO.h"

void Example_OPO_SingleSide()
{
    RT_OPO_SetSingleSideMode(ON, OFF, OFF, OFF, OPO_PSIDE);
    // 20-time amplification
    RT_OPO_SetAmplification(OPO_PIN_RESISTOR_1K, OPO_GAIN_20K, \
                            OPO_PIN_RESISTOR_1K, OPO_GAIN_20K);
    RT_ADC_Clear();
    RT_OPO_On();
}

void Example_OPO_DifferentialMode()
{
    RT_OPO_SetDifferentialMode(ON, OFF, OFF, OFF, OPO_NOT_EXCHANGE_PIN);
    // 20-time amplification
    RT_OPO_SetAmplification(OPO_PIN_RESISTOR_1K, OPO_GAIN_20K, \
                            OPO_PIN_RESISTOR_1K, OPO_GAIN_20K);
    RT_ADC_Clear();
    RT_OPO_On();
}

void Example_OPO_Calibration()
{
    RT_OPO_SetShort(ON);
}

void Example_OPO_Bypass()
{
    RT_OPO_SetBypass(ON);
}

```

## Sigma Delta

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
```

### Example

```C

#include "analogIO.h"

void Example_SD_Simplest()
{
    RT_ADC_SD_Setup(SD_CLK_3M, SD_20BIT, SD_TRIG_BY_WT2READ);
    // Turn on SD, clear SD, start accumulation are all done in RT_ADC_SD_Read
    uint32_t result = RT_ADC_SD_Read();
    // ...
}

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

## Voltage to Pulse Width

```C
void RT_ADC_V2P_On();

void RT_ADC_V2P_Off();

void RT_ADC_V2P_SetResistor();

uint32_t RT_ADC_V2P_Read();
```

## Internal Temperature Sensor

```C
void RT_ADC_TemperatureSensorOn();

void RT_ADC_TemperatureSensorOff();
```
