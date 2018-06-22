# Internal Temperature Sensor   {#InternalTemperatureSensor}

## Interface

```C
void RT_ADC_TemperatureSensorOn();

void RT_ADC_TemperatureSensorOff();
```

## Example

```C
#include "analogIO.h"

/* If you want to get an absolute value of the temperature,
 * you should make a calibration at first.
 */
void Example_InternalTemperatureSensor() {
    RT_ADC_TemperatureSensorOn();
    uint32_t result = RT_ADC_SD_Read();
}
```
