# TC0 Library for M2  {#TC0}

## Interface

```C
void RT_TC0_Stop();

void RT_TC0_ClearIrq();

void RT_TC0_ClearCnt();

void RT_TC0_ClearAll();

void RT_TC0_TcIrqOn();

void RT_TC0_TcIrqOff();

void RT_TC0_PWMIrqOn();

void RT_TC0_PWMIrqOff();

int  RT_TC0_CheckTcFlag();

int  RT_TC0_CheckPWMFlag();

void RT_TC0_TimerOn();

void RT_TC0_TimerOff();

void RT_TC0_TimerSet1us(T,irq);

void RT_TC0_SetCounter(n);

void RT_TC0_EcntOn();

void RT_TC0_EcntOff();

void RT_TC0_SetEcnt(n, trigger, irq);

void RT_TC0_PWMOn();

void RT_TC0_PWMOff();

void RT_TC0_SetPWM(div, ref, irq);

void RT_TC0_PWMMOn();

void RT_TC0_PWMMOff();

void RT_TC0_PWMMTriggerMode(mode);

void RT_TC0_SetPWMM(trigger, irq);

int  RT_TC0_ReadCnt();
```

## Example

```C
RT_TC0_ClearCnt();       // clear TC0 Counter
RT_TC0_TcIrqOn();        // set TC0 cnt-IRQ enable
```
