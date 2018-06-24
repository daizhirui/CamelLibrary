/**
 * @brief M2 micro core unit
 * @file mcu.h
 * @author Zhirui Dai
 * @date 2018-05-25
 */

#ifndef __M2_MCU__
#define __M2_MCU__

#include <stdint.h>

/**
 * @brief Keyword ON.
 */
#define ON      0x1
/**
 * @brief Keyword OFF.
 */
#define OFF     0x0

/**
 * @brief Keyword RAISE_TRIGGER.
 */
#define RAISE_TRIGGER   0x1
/**
 * @brief Keyword FALL_TRIGGER.
 */
#define FALL_TRIGGER    0x0

/**
 * @brief Hardware address
 */
// System
#define SYS_CTL0_REG         (unsigned long)0x1f800700 // sys control digi_off - - - - - dbg inten
#define SYS_CTL2_REG         (unsigned long)0x1f800702
#define SYS_IOCTL_REG        (unsigned long)0x1f800704 // 0=in; 1-out (16-bit), was IO config
#define SYS_IRQ_REG          (unsigned long)0x1f800707 // SYS INT IRQ read
// Interrupt
#define USER_INT             (unsigned long)0x01001FFC //interrupt is from user code if [0] is 1
#define PC_LOC               (unsigned long)0x01001FF8 //RAM address to store current program counter
#define INT_COUNT            (unsigned long)0x01001FF4 //RAM address to store current interrupt depth, number of interrupts
// External Interrupt
#define INT_CTL0_REG         (unsigned long)0x1f800500 // EX Int enable control and base
#define INT_CTL1_REG         (unsigned long)0x1f800501 // EX Int IRQ bits content read, (m1=03)
#define INT_CTL2_REG         (unsigned long)0x1f800502 // EX Int high enable
#define INT_CLR_REG          (unsigned long)0x1f800503 // EX Int IRQ clear  (m1=01)
// Uart0
#define UART0_READ_REG       (unsigned long)0x1f800000
#define UART0_BUSY_REG       (unsigned long)0x1f800001
#define UART0_WRITE_REG      (unsigned long)0x1f800002
#define UART0_IRQ_ACK_REG    (unsigned long)0x1f800003
#define UART0_CTL_REG        (unsigned long)0x1f800004
#define UART0_DATA_RDY_REG   (unsigned long)0x1f800005
#define UART0_LIN_BREAK_REG  (unsigned long)0x1f800006
#define UART0_BRP_REG        (unsigned long)0x1f800007
// Uart1
#define UART1_READ_REG       (unsigned long)0x1f800800
#define UART1_BUSY_REG       (unsigned long)0x1f800801
#define UART1_WRITE_REG      (unsigned long)0x1f800802
#define UART1_IRQ_ACK_REG    (unsigned long)0x1f800803
#define UART1_CTL_REG        (unsigned long)0x1f800804
#define UART1_DATA_RDY_REG   (unsigned long)0x1f800805
#define UART1_LIN_BREAK_REG  (unsigned long)0x1f800806
#define UART1_BRP_REG        (unsigned long)0x1f800807
// SPI
#define SPI_READ_REG         (unsigned long)0x1f800d00 // snoop read
#define SPI_BUSY_REG         (unsigned long)0x1f800d01
#define SPI_WRITE_REG        (unsigned long)0x1f800d02
#define SPI_IRQ_ACK_REG      (unsigned long)0x1f800d03 // clear IRQ when wt
#define SPI_CTL_REG          (unsigned long)0x1f800d04
#define SPI_DATA_RDY_REG     (unsigned long)0x1f800d05
// IO
#define SYS_GDR_REG          (unsigned long)0x1f800703 // gdr register
#define SYS_IOCTL_REG        (unsigned long)0x1f800704 // 0=in; 1-out (16-bit), was IO config
#define SYS_GPIO0_REG        (unsigned long)0x1f800705 // GPIO (16-bit) to pad content
#define SYS_GPIO1_REG        (unsigned long)0x1f800706 // GPIO (16_bit) from pad read
// TC0
#define T0_CTL0_REG          (unsigned long)0x1f800100 // T0 (32-bit)control and base
#define T0_REF_REG           (unsigned long)0x1f800101 // T0 ref number for PWM(1)
#define T0_READ_REG          (unsigned long)0x1f800102 // T0 value
#define T0_CLRIRQ_REG        (unsigned long)0x1f800103 // T0 clear IRQ
#define T0_CLK_REG           (unsigned long)0x1f800104 // T0 clk div
#define T0_CLRCNT_REG        (unsigned long)0x1f800105 // T0 clear counter content (and PWM)
// TC1
#define T1_CTL0_REG          (unsigned long)0x1f800200 // Timer1 (32-bit)control and base
#define T1_REF_REG           (unsigned long)0x1f800201 // Timer1 ref number for PWM(1)
#define T1_READ_REG          (unsigned long)0x1f800202 // Timer1 value
#define T1_CLRIRQ_REG        (unsigned long)0x1f800203 // Timer1 clear IRQ
#define T1_CLK_REG           (unsigned long)0x1f800204 // Timer1 clk div
#define T1_CLRCNT_REG        (unsigned long)0x1f800205 // Timer1 clear counter content (and PWM)
// TC2
#define T2_CTL0_REG          (unsigned long)0x1f800400 // Timer2 (32-bit)control and base
#define T2_REF_REG           (unsigned long)0x1f800401 // Timer2 ref number for PWM(4, 32bit)
#define T2_READ_REG          (unsigned long)0x1f800402 // Timer2 value
#define T2_CLRIRQ_REG        (unsigned long)0x1f800403 // Timer2 clear IRQ
#define T2_CLK_REG           (unsigned long)0x1f800404 // Timer2 clk div
#define T2_CLRCNT_REG        (unsigned long)0x1f800405 // Timer2 clear counter content (and PWM)
#define T2_PHASE_REG         (unsigned long)0x1f800406 // Timer2 PWM phase reg (32b, 4 pwm)
// TC4
#define T4_CTL0_REG          (unsigned long)0x1f800a00 // Timer8-4 (2-bit) enable control
#define T4_REF0_REG          (unsigned long)0x1f800a01 // Timer8-4 ref number for PWM0 buz(8-bit)
#define T4_CLK0_REG          (unsigned long)0x1f800a02 // Timer8-4 clk div for PWM0 (8-bit)
#define T4_REF1_REG          (unsigned long)0x1f800a03 // Timer8-4 ref number for PWM1 fast(4-bit)
#define T4_CLK1_REG          (unsigned long)0x1f800a04 // Timer8-4 clk div for PWM1 (8-bit)
// Analog
#define AD_CTL0_REG          (unsigned long)0x1f800600 // SD and V2P control (16-bit)
#define AD_OPO_REG           (unsigned long)0x1f800601 // OPO and Chan control (16-bit)
#define AD_READ_REG          (unsigned long)0x1f800602 // SD df read (16-bit)
#define AD_CLR_REG           (unsigned long)0x1f800603 // SD ADC clear reg
// LCD
#define LCD_CTL0_REG         (unsigned long)0x1f800300 // LCD control
#define LCD_RAM_REG          (unsigned long)0x1f800380 // LCD ram starting (80-8C)
#define LCD_RAM_LINE0        (unsigned long)0x1f800380 // LCD ram line0 (80-8C)
#define LCD_RAM_LINE1        (unsigned long)0x1f800384 // LCD ram line1 (80-8C)
#define LCD_RAM_LINE2        (unsigned long)0x1f800388 // LCD ram line2 (80-8C)
#define LCD_RAM_LINE3        (unsigned long)0x1f80038c // LCD ram line3 (80-8C)
// Watch Dog
#define WDT_CTL0_REG         (unsigned long)0x1f800b00 // WDT control
#define WDT_CLR_REG          (unsigned long)0x1f800b03 // WDT clear reg
#define WDT_READ_REG         (unsigned long)0x1f800b02 // WDT read reg
// Real time module
#define RTC_CTL_REG          (unsigned long)0x1f800f00
#define RTC_TIME_REG         (unsigned long)0x1f800f01 // time
#define RTC_CLR_REG          (unsigned long)0x1f800f03

#define DATA_SIZE 256

/*! \cond PRIVATE */
#define MemoryRead(A) (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)
#define MemoryOr(A,V) (*(volatile unsigned int*)(A)|=(V))
#define MemoryAnd(A,V) (*(volatile unsigned int*)(A)&=(V))
/*! \endcond */

/**
 * @brief Read 32-bit data from a specific address.
 * @param
 */
#define MemoryRead32(addr) (*(volatile unsigned long*)(addr))

/**
 * @brief Write 32-bit data to a specific address.
 */
#define MemoryWrite32(addr,val) *(volatile unsigned long*)(addr)=(val)

/**
 * @brief Logical OR operation on 32-bit data from a specific address.
 */
#define MemoryOr32(addr,val) (*(volatile unsigned long*)(addr)|=(val))

/**
 * @brief Logical addrND operation on 32-bit data from a specific address.
 */
#define MemoryAnd32(addr,val) (*(volatile unsigned long*)(addr)&=(val))

/**
 * @brief Get a specific bit of a 32-bit data from a specific address.
 */
#define MemoryBitAt(addr,val) ((*(volatile unsigned long*)(addr)&=(1<<(val)))>>(val))

/**
 * @brief Set a specific bit of a 32-bit data from a specific address to 1.
 */
#define MemoryBitOn(addr,val) MemoryOr32(addr,1<<(val))

/**
 * @brief Set a specific bit of a 32-bit data from a specific address to 0.
 */
#define MemoryBitOff(addr,val) MemoryAnd32(addr,~(1<<(val)))

/**
 * @brief Set a specific bit of a 32-bit data from a specific address to opposite state.
 */
#define MemoryBitSwitch(addr,val) (*(volatile unsigned long*)(addr)^=(1<<(val)))

/**
 * @brief Function pointer type (void)->void definition.
 */
typedef void (*FuncPtr)(void);

/**
 * @brief Function pointer type (unsigned long)->void definition.
 */
typedef void (*FuncPtr1)(unsigned long);

/**
 * @brief Function pointer type (unsigned long, unsigned long)->void definition.
 */
typedef void (*FuncPtr2)(unsigned long, unsigned long);

/**
 * @brief Jump to a specific address.
 */
#define JumpTo(address)             \
    {                               \
        FuncPtr funcptr;            \
        funcptr = (FuncPtr)address; \
        funcptr();                  \
    }

#define SYS_CLK_3M  (0x0<<12)
#define SYS_CLK_6M  (0x1<<12)
#define SYS_CLK_12M (0x3<<12)

#define RT_MCU_SetSystemClock(mode)                 \
    {                                               \
        MemoryAnd32(SYS_CTL2_REG, ~SYS_CLK_12M);    \
        MemoryOr32(SYS_CTL2_REG, mode);             \
    }

void RT_Clr_Sram();

#endif // End of __M2_MCU__
