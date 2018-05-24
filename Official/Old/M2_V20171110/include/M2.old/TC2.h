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
#ifndef __TC2_H__
#define __TC2_H__


/*********** Hardware addesses ***********/

#define T2_CTL0_REG       0x1f800400  // Timer2 (32-bit)control and base
#define T2_REF_REG        0x1f800401  // Timer2 ref number for PWM(4, 32bit)
#define T2_READ_REG       0x1f800402  // Timer2 value
#define T2_CLRIRQ_REG     0x1f800403  // Timer2 clear IRQ
#define T2_CLK_REG        0x1f800404  // Timer2 clk div
#define T2_CLRCNT_REG     0x1f800405  // Timer2 clear counter content (and PWM)
#define T2_PHASE_REG      0x1f800406  // Timer2 PWM phase reg (32b, 4 pwm)

/***** Timer clr stop and flag Setup******/
void RT_T2_Stop();
void RT_T2_Clr();
int  RT_T2_Flag();
/****************** end*******************/

/*********** Timer2 cnt Setup*************/
void RT_T2_Set100u(int n, int irq);
void RT_T2_Set1u(int n, int irq);
void RT_T2_SetTimer(int scale, int n, int irq);
/************Timer2 cnt End***************/

/*********** Timer2 PWM Setup*************/
void RT_T2_PWM(int div, int ref, int phase0, int phase1, int phase2, int phase3, int pwm0, int pwm13);
/*********** Timer2 PWM End***************/

/*********** Timer2 ECM Setup*************/
void RT_T2_Ecnt(int n,int pos, int irq);
/*********** Timer2 ECM End***************/

/*********** Timer2 PWMM Setup*************/
void RT_T2_PulseWidth(int rise, int irq);
int RT_T2_ReadCnt();
/*********** Timer2 PWMM End***************/

#endif //__T2_H__
