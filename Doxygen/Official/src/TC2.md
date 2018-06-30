# TC2 Library for M2  {#TC2}

## Interface

```C
void RT_TC2_Stop();

void RT_TC2_ClearIrq();

void RT_TC2_ClearCnt();

void RT_TC2_ClearAll();

void RT_TC2_TcIrqOn();

void RT_TC2_TcIrqOff();

void RT_TC2_PWMIrqOn();

void RT_TC2_PWMIrqOff();

int  RT_TC2_CheckTcFlag();

int  RT_TC2_CheckPWMFlag();

void RT_TC2_TimerOn();

void RT_TC2_TimerOff();

void RT_TC2_TimerSet1us(T,irq);

void RT_TC2_SetCounter(n);

void RT_TC2_EcntOn();

void RT_TC2_EcntOff();

void RT_TC2_SetEcnt(n, trigger, irq);

void RT_TC2_PWM0On();

void RT_TC2_PWM0Off();

void RT_TC2_PWM1to3On();

void RT_TC2_PWM1to3Off();

void RT_TC2_SetAllPWM(div, duty0, duty1, duty2, duty3, phase0, phase1, phase2, phase3, pwm0, pwm13);

void RT_TC2_PWMMOn();

void RT_TC2_PWMMOff();

void RT_TC2_PWMMTriggerMode(mode);

void RT_TC2_SetPWMM(trigger, irq);

int  RT_TC2_ReadCnt();
```

## Example

```C
RT_TC2_ClearCnt();       // clear TC2 Counter
RT_TC2_TcIrqOn();        // set TC2 cnt-IRQ enable
```
