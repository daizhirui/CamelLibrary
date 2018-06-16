/**
* @file SPI.c
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief SPI Library for M2
*/
#include "SPI.h"
/**
 * @brief   Read 1 byte from SPI
 * @return unsigned char 1-byte data from SPI
 */
unsigned char RT_SPI_Read()
{
    while (!RT_SPI_DataReady())
        ;
    return RT_SPI_Read_();
}
/**
 * @brief       Transfer data when M2's SPI works as Master
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
 * @brief       Transfer data when M2's SPI works as Slave
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char RT_SPI_SlaveTransfer(unsigned char c)
{
    unsigned char tmp = RT_SPI_Read();
    RT_SPI_Write_(c);
    return tmp;
}
/**
 * @brief   Make a delay.
 * @note    This function is used only when the other SPI device is not fast enough.
 * @return  void
 */
void RT_SPI_delay(){
    register int i;
    for(i=0;i<2;i++)
        __asm__("nop");
}
