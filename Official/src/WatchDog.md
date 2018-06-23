# Watch Dog Library for M2  {#WDT}

## Interface

```C
void RT_WatchDog_Setup(n, irq, rst);

void RT_WatchDog_Clear();

uint4_t RT_WatchDog_ReadValue();
```

## Example

```C
RT_WDT_Clr();       // clear watch dog
RT_WDT_Set(8,0,1);  // set as 1s (8 * 1/8s), no interrupt, auto-reset
```
