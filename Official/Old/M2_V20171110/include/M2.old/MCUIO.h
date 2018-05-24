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
#ifndef __MCUIO_H__
#define __MCUIO_H__


/*********** Hardware addesses ***********/
#define SYS_IOCTL_REG     0x1f800704  // 0=in; 1-out (16-bit), was IO config
#define SYS_GPIO0_REG     0x1f800705  // GPIO (16-bit) to pad content 
#define SYS_GPIO1_REG     0x1f800706  // GPIO (16_bit) from pad read 

#define SET_GPIO0_BIT_ON(A) {MemoryOr32(SYS_IOCTL_REG, (1<<A)); MemoryOr32(SYS_GPIO0_REG, (1<<A)); }
#define SET_GPIO0_BIT_OFF(A) {MemoryOr32(SYS_IOCTL_REG, (1<<A)); MemoryAnd32(SYS_GPIO0_REG, ~(1<<A)); }
#define GET_GPIO1_BIT(A) MemoryBitAt(SYS_GPIO1_REG, A)

/*************** IO Setup***************/
void RT_IOCTL_Set1(int n, int oe);
void RT_IOCTL_Set16(int oe);
void RT_IOCTL_And16(int oe);
void RT_IOCTL_Or16(int oe);
void RT_GPIO_Write1(int n, int v);
int  RT_GPIO_Read1(int n);
int  RT_GPIO_Read16();
void RT_GPIO_Write16(int v);
/**************** IO End****************/

#endif //__MCUIO_H__
