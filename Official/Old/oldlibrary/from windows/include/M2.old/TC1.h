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
#ifndef __TC1_H__
#define __TC1_H__

#define T1_CTL0_REG       0x1f800200  // Timer1 (32-bit)control and base
#define T1_REF_REG        0x1f800201  // Timer1 ref number for PWM(1)
#define T1_READ_REG       0x1f800202  // Timer1 value
#define T1_CLRIRQ_REG     0x1f800203  // Timer1 clear IRQ
#define T1_CLK_REG        0x1f800204  // Timer1 clk div
#define T1_CLRCNT_REG     0x1f800205  // Timer1 clear counter content (and PWM)

/***** Timer clr stop and flag Setup******/
void RT_T1_Stop();
void RT_T1_Clr();
void RT_T1_SetIRQ(unsigned int state);
int  RT_T1_Flag();
/****************** end*******************/

/*********** Timer1 cnt Setup*************/
void RT_T1_Set100u(int n, int irq);
void RT_T1_Set1u(int n, int irq);
void RT_T1_SetTimer(int scale, int n, int irq);
/*********** Timer1 cnt End***************/

/*********** Timer1 PWM Setup*************/
void RT_T1_PWM(int div, int ref, int irq);
/*********** Timer1 PWM End***************/

/*********** Timer1 ECM Setup*************/
void RT_T1_Ecnt(int n,int pos, int irq);
/*********** Timer1 ECM End***************/

/*********** Timer1 PWMM Setup*************/
void RT_T1_PulseWidth(int rise, int irq);
int RT_T1_ReadCnt();
/*********** Timer1 PWMM End***************/

#endif
