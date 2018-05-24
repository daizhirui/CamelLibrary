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
unsigned char SPI_Read()
{
    while (!SPI_DataReady())
        ;
    return SPI_Read_();
}
/**
 * @brief This function transfers data when M2's SPI works as Master
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char SPI_MasterTransfer(unsigned char c)
{
    SPI_Write(c);
    return SPI_Read();
}
/**
 * @brief This function transfers data when M2's SPI works as Slave
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char SPI_SlaveTransfer(unsigned char c)
{
    unsigned char tmp = SPI_Read();
    SPI_Write_(c);
    return tmp;
}
void SPI_delay(){
    register int i;
    for(i=0;i<2;i++);
}
