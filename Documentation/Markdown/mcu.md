# Micro Control Unit (MCU) Library for M2  {#mcu}

To use this library, please include `mcu.h`.

## Interface

```C
long MemoryRead32(addr);

void MemoryWrite32(addr,val);

void MemoryOr32(addr,val);

void MemoryAnd32(addr,val);

void MemoryBitAt(addr,val);

void MemoryBitOn(addr,val);

void MemoryBitOff(addr,val);

void MemoryBitSwitch(addr,val);

void RT_MCU_JumpTo(unsigned long address);

void RT_MCU_SetSystemClock(uint32_t mode);

void RT_Sram_Clear();
```

## Example

```C
long a = MemoryRead32(0x1000000);      // read the value @0x1000000
```
