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
#ifndef __TC0_H__
#define __TC0_H__

#define T0_CTL0_REG       0x1f800100  // Timer0 (32-bit)control and base
#define T0_REF_REG        0x1f800101  // Timer0 ref number for PWM(1)
#define T0_READ_REG       0x1f800102  // Timer0 value
#define T0_CLRIRQ_REG     0x1f800103  // Timer0 clear IRQ
#define T0_CLK_REG        0x1f800104  // Timer0 clk div
#define T0_CLRCNT_REG     0x1f800105  // Timer0 clear counter content (and PWM)

/***** Timer clr stop and flag Setup******/
void RT_T0_Stop();
void RT_T0_Clr();
int  RT_T0_Flag();
/****************** end*******************/

/*********** Timer0 cnt Setup*************/
void RT_T0_Set100u(int n, int irq);
void RT_T0_Set1u(int n, int irq);
void RT_T0_SetTimer(int scale, int n, int irq);
/*********** Timer0 cnt End***************/

/*********** Timer0 PWM Setup*************/
void RT_T0_PWM(int div, int ref, int irq);
/*********** Timer0 PWM End***************/

/*********** Timer0 ECM Setup*************/
void RT_T0_Ecnt(int n,int pos, int irq);
/*********** Timer0 ECM End***************/

/*********** Timer0 PWMM Setup*************/
void RT_T0_PulseWidth(int rise, int irq);
int RT_T0_ReadCnt();
/*********** Timer0 PWMM End***************/

#endif
