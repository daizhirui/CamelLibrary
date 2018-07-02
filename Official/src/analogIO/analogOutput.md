# Analog Output Library for M2  {#analogOutput}

To use this library, please include `analogIO.h` and `soft_fp.h`.

**ATTENTION**

- Because analog value ranges from 0 to the voltage of p_vdd5, you must use soft float library!
- To get a smoother output, please connect a low-pass filter, a capacity, to the pin you set as analog output.

## Description

This library provides the function of DAC (Digital to Analog Converter) by using the PWM0 of Timer Counter 0, 1 and 2. When `RT_ADC_analogWrite` is used, the frequency of the corresponding timer is changed. If you want to custom the timer frequency, please change it later.

## Interface

```C
void RT_ADC_analogWrite(channel, value, p_vdd5);
```

## Example

```C
// set analog output channel 0 to output 1.5v.
RTC_ADC_analogWrite(ANALOG_OUTPUT_0, 1.5, 5.0);
```
