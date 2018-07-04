# Amplifier (OPO)   {#OPO}

To use this library, please include `analogIO.h`.

## Interface

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

void RT_ADC_Clear();
```

## Example

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
