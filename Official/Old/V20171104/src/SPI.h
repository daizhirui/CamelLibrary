/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/10/31
 * FILENAME: SPI.h
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *--------------------------------------------------------------------*/
#ifndef __SPI_h__
#define __SPI_h__

#include "mcu.h"
#include "UART1.h"
/*********** Hardware addesses ***********/
#define SPI_READ        0x1f800d00 // snoop read
#define SPI_BUSY        0x1f800d01
#define SPI_WRITE       0x1f800d02
#define SPI_IRQ_ACK     0x1f800d03 // clear IRQ when wt
#define SPI_CTL         0x1f800d04
#define SPI_DATA_RDY    0x1f800d05
/************** Value define *************/
#define MASTER 0x1
#define SLAVE 0x0
/*************** SPI Setup***************/
#define SPI_ClearState() MemoryWrite32(SPI_IRQ_ACK, 0x6)
#define SPI_Modeset(MorS)                \
    {                                    \
        UART1_Off();                     \
        if (MorS)                        \
            MemoryWrite32(SPI_CTL, 0x4); \
        else                             \
            MemoryWrite32(SPI_CTL, 0x0); \
        SPI_ClearState();                \
    }
#define SPI_ChipSelect() MemoryWrite32(SPI_CTL, 0x6)
#define SPI_ChipRelease() MemoryWrite32(SPI_CTL, 0x4)
#define SPI_Busy() MemoryRead32(SPI_BUSY)
#define SPI_Write_(val) MemoryWrite32(SPI_WRITE, val)
#define SPI_Write(val)     \
    {                      \
        while (SPI_Busy()) \
            ;              \
        SPI_Write_(val);   \
        while (SPI_Busy()) \
            ;              \
    }
#define SPI_DataReady() MemoryRead32(SPI_DATA_RDY)
#define SPI_Read_() MemoryRead32(SPI_READ)
/**
 * @brief This function returns 1 byte from SPI
 * 
 * @return unsigned char 1-byte data from SPI
 */
unsigned char SPI_Read();
/**
 * @brief This function transfers data when M2's SPI works as Master
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char SPI_MasterTransfer(unsigned char c);
/**
 * @brief This function transfers data when M2's SPI works as Slave
 * 
 * @param c     1-byte data to send
 * @return unsigned char 1-byte data received
 */
unsigned char SPI_SlaveTransfer(unsigned char c);
#define SPI_Off()   MemoryOr32(SPI_CTL, 0x8)
#define SPI_On()    MemoryAnd32(SPI_CTL, ~0x8)
void SPI_delay();    
#endif
