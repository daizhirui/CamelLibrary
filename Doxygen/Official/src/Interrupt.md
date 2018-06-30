# Interrupt Library for M2  {#Interrupt}

## Interface

```C
int  RT_SYSINT_GetFlag(device);

void RT_SYSINT_On();

void RT_SYSINT_Off();

void RT_EXTINT_Setup(port, trigger);

void RT_EXTINT_Off(port);

void RT_EXTINT_Clear(port);

void RT_EXTINT_ClearAll();

int  RT_EXTINT_GetAllFlag();

int  RT_EXTINT_GetFlag(port);
```

## Example

```C
RT_SYSINT_On();             // turn on system interrupt
RT_EXTINT_Clear(1);         // clear External Interrupt port 1
```
