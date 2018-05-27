/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/10/31
 * FILENAME: SPI.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *--------------------------------------------------------------------*/
#include "SPI.h"
/**
 * @brief This function returns 1 byte from SPI
 * 
 * @return unsigned char 1-byte data from SPI
 */
unsigned char RT_SPI_Read()
{
    while (!RT_SPI_DataReady())
        ;
    return RT_SPI_Read_();
}
/**
 * @brief This function transfers data when M2's SPI works as Master
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char RT_SPI_MasterTransfer(unsigned char c)
{
    RT_SPI_Write(c);
    return RT_SPI_Read();
}
/**
 * @brief This function transfers data when M2's SPI works as Slave
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char RT_SPI_SlaveTransfer(unsigned char c)
{
    unsigned char tmp = RT_SPI_Read();
    RT_SPI_Write_(c);
    return tmp;
}
void RT_SPI_delay(){
    register int i;
    for(i=0;i<2;i++);
}
