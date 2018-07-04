# TC1 Library for M2  {#TC1}

To use this library, please include `TC1.h`.

## Interface

```C
void RT_TC1_Stop();

void RT_TC1_ClearIrq();

void RT_TC1_ClearCnt();

void RT_TC1_ClearAll();

void RT_TC1_TcIrqOn();

void RT_TC1_TcIrqOff();

void RT_TC1_PWMIrqOn();

void RT_TC1_PWMIrqOff();

int  RT_TC1_CheckTcFlag();

int  RT_TC1_CheckPWMFlag();

void RT_TC1_TimerOn();

void RT_TC1_TimerOff();

void RT_TC1_TimerSet1us(T,irq);

void RT_TC1_SetCounter(n);

void RT_TC1_EcntOn();

void RT_TC1_EcntOff();

void RT_TC1_SetEcnt(n, trigger, irq);

void RT_TC1_PWMOn();

void RT_TC1_PWMOff();

void RT_TC1_SetPWM(div, ref, irq);

void RT_TC1_PWMMOn();

void RT_TC1_PWMMOff();

void RT_TC1_PWMMTriggerMode(mode);

void RT_TC1_SetPWMM(trigger, irq);

int  RT_TC1_ReadCnt();
```

## Example

```C
RT_TC1_ClearCnt();       // clear TC1 Counter
RT_TC1_TcIrqOn();          // set TC1 cnt-IRQ enable
```
