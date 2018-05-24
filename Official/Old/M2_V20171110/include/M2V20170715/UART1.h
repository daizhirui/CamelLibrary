/*--------------------------------------------------------------------
 * TITLE: m2 Hardware Defines
 * AUTHOR: Bill
 * DATE CREATED: 2017/05/30
 * FILENAME: uart1.h
 * PROJECT: m2
 * COPYRIGHT: Small World, Inc.
 * DESCRIPTION:
 *    m2 Hardware Defines
 *
 *    2017-05-30: base function for uart1
 *     *--------------------------------------------------------------------*/
#ifndef __UART1_H__
#define __UART1_H__


/*********** Hardware addesses ***********/
#define PRINT1_PORT        0x1f800802
#define UART1_WRITE        0x1f800802
#define UART1_READ         0x1f800800  // snoop read
#define UART1_DATA_RDY     0x1f800805
#define UART1_CTL          0x1f800804
#define UART1_IRQ_ACK      0x1f800803  // clear IRQ when wt
#define UART1_BUSY         0x1f800801
#define uart1_bport         0x1f800801 // uart busy port
#define uart1_wport         0x1f800802
#define uart1_rport         0x1f800800
#define uart1_rdy_port      0x1f800805
#define uart1_aport         0x1f800803 // read ack port
#define WRITE_BUSY         0x0001
#define READ_RDY           0x0001
/*************** UART Setup***************/
#define RT_UART1_Busy()	(*(volatile unsigned *)UART1_BUSY)
#define RT_UART1_DataRdy() 	(*(volatile unsigned int*)uart1_rdy_port)
#define RT_UART1_Read()	(*(volatile unsigned*)uart1_rport)
#define RT_UART1_IRQ()	(*(volatile unsigned long*)(UART1_CTL) = 1)
#define RT_UART1_CLRIRQ()	(*(volatile unsigned long*)(UART1_CTL) = 0)
#define RT_UART1_Off() 	*(volatile unsigned long*)(UART1_CTL) = 0x10
void RT_UART1_WriteChar(unsigned char value);
void RT_UART1_WriteShort(unsigned short value);
void RT_UART1_WriteLong(unsigned long value);
void RT_UART1_WriteLongLong(long long value);
void RT_UART1_WriteString(unsigned char * string);
void RT_UART1_WriteLongArray(unsigned long * data, unsigned long num);
unsigned char RT_UART1_WaitRead();
/**************** UART End****************/

#endif //__UART1_H__
