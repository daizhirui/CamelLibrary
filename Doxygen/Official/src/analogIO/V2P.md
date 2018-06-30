# Voltage to Pulse Width    {#V2P}

## Interface

```C
void RT_ADC_V2P_On();

void RT_ADC_V2P_Off();

void RT_ADC_V2P_SetResistor();

uint32_t RT_ADC_V2P_Read();

void RT_ADC_Clear();
```

## Example

```C
#include "analogIO.h"

void Example_V2P() {
    RT_ADC_V2P_On();
    RT_ADC_V2P_SetResistor(V2P_220K);   // V2P_185K is set in single side mode of the amplifier.
    uint32_t result = RT_ADC_V2P_Read();
}
```
