/**
* @file SPI.c
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief SPI Library for M2
*/
#include "SPI.h"

unsigned char RT_SPI_Read()
{
    while (!RT_SPI_DataReady())
        ;
    return RT_SPI_Read_();
}

unsigned char RT_SPI_MasterTransfer(unsigned char c)
{
    RT_SPI_Write(c);
    return RT_SPI_Read();
}

unsigned char RT_SPI_SlaveTransfer(unsigned char c)
{
    unsigned char tmp = RT_SPI_Read();
    RT_SPI_Write_(c);
    return tmp;
}

void RT_SPI_Delay(){
    register int i;
    for(i=0;i<2;i++)
        __asm__("nop");
}
