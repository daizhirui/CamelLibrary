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
#ifndef __WDT_H__
#define __WDT_H__


/*********** Hardware addesses ***********/
// this is Watch dog timer
#define WDT_CTL0_REG      0x1f800b00  // WDT control
#define WDT_CLR_REG       0x1f800b03  // WDT clear reg
#define WDT_READ_REG      0x1f800b02  // WDT read reg

/*************** WDT Setup***************/
void RT_WDT_Set(int n, int irq, int rst);
void RT_WDT_Clr();
/**************** WDT End****************/

#endif //__WDT_H__
