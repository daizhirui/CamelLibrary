/*--------------------------------------------------------------------
 * TITLE: m2 Hardware Defines
 * AUTHOR: John & Jack 
 * DATE CREATED: 2013/10/10
 * FILENAME: m2.h
 * PROJECT: m2
 * COPYRIGHT: Small World, Inc.
 * DESCRIPTION:
 *    m2 Hardware Defines
 *
 *    2014-03-17: added sd adc, opo, v2p; sys reg modified
 *    2014-01-11: added sd adc, opo, v2p; sys reg modified
 *    2013-12-18: misc edit
 *    2013-12-15: uart reg back to m1
 *    2012-10-16: modified base on m2 new design
 *    2012-10-10: modified base on s0.h
 *--------------------------------------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__


/*********** Hardware addesses ***********/

// SPI
#define SPI_WRITE         0x1f800d02
#define SPI_READ          0x1f800d00  // snoop read
#define SPI_DATA_RDY      0x1f800d05
#define SPI_CTL           0x1f800d04
#define SPI_IRQ_ACK       0x1f800d03  // clear IRQ when wt
#define SPI_BUSY          0x1f800d01

/*************** SPI Setup***************/
void RT_SPI_ModeSet( int MorS);
void RT_SPI_Write(unsigned long val);
unsigned int RT_SPI_DataRdy();
unsigned long RT_SPI_Read();
unsigned int RT_SPI_Busy();
/**************** SPI End****************/

#endif //__SPI_H__
