# SPI Library For M2    {#SPI}

To use this library, please include `SPI.h`.

## Interface

```C
void RT_SPI_On();

void RT_SPI_Off();

void RT_SPI_Modeset(MorS);

void RT_SPI_ChipSelect();

void RT_SPI_ChipRelease();

void RT_SPI_ClearState();

void RT_SPI_Busy();

void RT_SPI_Write_(val);

void RT_SPI_Write(val);

uint32_t RT_SPI_DataReady();

uint8_t RT_SPI_Read_();

unsigned char RT_SPI_Read();

unsigned char RT_SPI_MasterTransfer(unsigned char c);

unsigned char RT_SPI_SlaveTransfer(unsigned char c);

void RT_SPI_Delay();
```

## Example

```C
#include "SPI.h"
#include "stdio.h"

// This example shows how to set M2 SPI as master, send and receive data.
void master(){
    char c;
    RT_SPI_Modeset(MASTER);             // set M2 SPI as Master
    RT_SPI_ChipSelect();
    RT_SPI_ClearState();
    while(1){
        c=RT_SPI_MasterTransfer('A');
        putchar(c);
    }
}

// This example shows how to set M2 SPI as slave, send and receive data.
void slave(){
    char c;
    RT_SPI_Modeset(SLAVE);              // set M2 SPI as Slave
    RT_SPI_ClearState();
    RT_SPI_Write_('B');
    while(1){
        c=RT_SPI_SlaveTransfer('B');
        putchar(c);
    }
}
```
