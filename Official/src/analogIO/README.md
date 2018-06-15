# Analog Input Output Library for M2

## Interface

### Sigma Delta Converter (SD) of Analog Digit Converter (ADC)

#### RT_ADC_SD_On

Turn on SD.

- Definition

```C
void RT_ADC_SD_On();
```

#### RT_ADC_SD_Off

Turn off SD.

- Definition

```C
void RT_ADC_SD_Off();
```

#### RT_ADC_SD_Setup

Simply setup SD with specific sample rate and ad width.

- Definition

```C
void RT_ADC_SD_Setup(sampleRate, adWidth, triggerSource);
```

- Parameter
    - sampleRate: The sample rate, decided by the clock frequency, `SD_CLK_3M`, `SD_CLK_1_5M`, `SD_CLK_781K` or `SD_CLK_390K`.
    - adWidth: The length of a result, `SD_14BIT`, `SD_16BIT`, `SD_18BIT` or `SD_20BIT`. This decides the precision of the result.
    - triggerSource: The source to trig sampling, `SD_TRIG_BY_TC0PWM` or `SD_TRIG_BY_WT2READ`.

#### RT_ADC_SD_SetSampleRate

Set the sample rate of SD.

- Definition

```C
void RT_ADC_SD_SetSampleRate(mode);
```

- Parameter
    - mode: The sample rate, decided by the clock frequency, `SD_CLK_3M`, `SD_CLK_1_5M`, `SD_CLK_781K` or `SD_CLK_390K`.

#### RT_ADC_SD_SetAdWidth

Set the length of the result. This length decides the result precision.

- Definition

```C
void RT_ADC_SD_SetAdWidth(mode);
```

- Parameter:
    - mode: The length of a result, `SD_14BIT`, `SD_16BIT`, `SD_18BIT` or `SD_20BIT`.

#### RT_ADC_SD_SetTrigger

Set the source to trig sampling.

- Definition

```C
void RT_ADC_SD_SetTrigger(source);
```

- Parameter:
    - source: The source to trig sampling, `SD_TRIG_BY_TC0PWM` or `SD_TRIG_BY_WT2READ`.

#### RT_ADC_SD_Start

Turn on SD and trig df accumulation. When the accumulation is completed, SD irq flag will be raised.

- Definition

```C
void RT_ADC_SD_Start();
```

#### RT_ADC_SD_Read
Read the result of SD when it is ready.

- Definition

```C
uint32_t RT_ADC_SD_Read();
```

#### RT_ADC_SD_DataReady
Check is the accumulation is completed.

- Definition

```C
void RT_ADC_SD_DataReady();
```

#### RT_ADC_Clear
Clear SD.

- Definition

```C
void RT_ADC_Clear();
```

### Amplifier (OPO)

#### RT_OPO_On
#### RT_OPO_Off
#### RT_OPO_SetChannel
#### RT_OPO_SetSingleSideMode
#### RT_OPO_SetDifferentialMode
#### RT_OPO_SetAmplification
#### RT_OPO_SetPsideFeedback
#### RT_OPO_SetPNExchange
#### RT_OPO_SetShort
#### RT_OPO_SetBypass
#### RT_OPO_SetPsideGND


### Voltage To Pulse Width (V2P)

#### RT_ADC_V2P_On
#### RT_ADC_V2P_Off
#### RT_ADC_V2P_SetRes
#### RT_ADC_V2P_Read

### Internal Temperature Sensor

#### RT_ADC_TemperatureSensorOn
#### RT_ADC_TemperatureSensorOff
