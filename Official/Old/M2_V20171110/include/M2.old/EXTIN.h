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
#ifndef __EXTIN_H__
#define __EXTIN_H__


/*********** Hardware addesses ***********/
#define INT_CTL0_REG      0x1f800500  // EX Int enable control and base
#define INT_CTL1_REG      0x1f800501  // EX Int IRQ bits content read, (m1=03) 
#define INT_CTL2_REG      0x1f800502  // EX Int high enable 
#define INT_CLR_REG       0x1f800503  // EX Int IRQ clear  (m1=01)
#define SYS_CTL0_REG      0x1f800700  // sys control digi_off - - - - - dbg inten

/*********** External interrupt***********/
void RT_EXINT_Set(int en, int trigger);
void RT_EXINT_Clr();
int  RT_EXINT_Flag();
/*********** External interrupt end*******/

#endif //__EXTIN_H__
