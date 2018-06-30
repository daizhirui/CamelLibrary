# Real Time Counter Library for M2  {#RTC}

To use this library, please include `time.h`.

## Interface

```C
void RT_RTC_On()

void RT_RTC_Off()

void RT_RTC_SetTimeFormat(format)

void RT_RTC_SetTime(year, month, day, hour, min, sec)

long RT_RTC_Read32()

void RT_RTC_GetTime(unsigned char *d_year, unsigned char *d_mon, unsigned char *d_day,
               unsigned char *d_hour, unsigned char *d_min, unsigned char *d_sec);

void RT_DelayMiliseconds(unsigned long ms);
```

## Example

```C
RT_RTC_On();     // turn on RTC
RT_RTC_Off();    // turn off RTC
```
