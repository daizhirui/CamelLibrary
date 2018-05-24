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
#ifndef __TC4_H__
#define __TC4_H__


/*********** Hardware addesses ***********/

// this is PWM/Bz unit, has two PWMs
#define T4_CTL0_REG       0x1f800a00  // Timer8-4 (2-bit) enable control 
#define T4_REF0_REG       0x1f800a01  // Timer8-4 ref number for PWM0 buz(8-bit)
#define T4_CLK0_REG       0x1f800a02  // Timer8-4 clk div for PWM0 (8-bit)
#define T4_REF1_REG       0x1f800a03  // Timer8-4 ref number for PWM1 fast(4-bit)
#define T4_CLK1_REG       0x1f800a04  // Timer8-4 clk div for PWM1 (8-bit)

/***** Timer clr stop and flag Setup******/
void RT_T4_Stop();
/****************** end*******************/

/*********** Timer4 PWM Setup*************/
void RT_T4_PWM(int pwm0_en, int div0, int ref0, int pwm1_en, int div1, int ref1);
/*********** Timer4 PWM End***************/

#endif //__T4_H__
