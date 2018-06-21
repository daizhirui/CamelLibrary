/**
* @file UART.h
* @author Zhirui Dai
* @date 31 Oct 2017
* @copyright 2018 Zhirui
* @brief UART Library for M2
*/
#ifndef __UART_h__
#define __UART_h__

#include "mcu.h"

#define UART0   0x0
#define UART1   0x1

#define UART_CTL_REG(port)          (port? UART1_CTL_REG : UART0_CTL_REG)
#define UART_BUSY_REG(port)         (port? UART1_BUSY_REG : UART0_BUSY_REG)
#define UART_WRITE_REG(port)        (port? UART1_WRITE_REG : UART0_WRITE_REG)
#define UART_DATA_RDY_REG(port)     (port? UART1_DATA_RDY_REG : UART0_DATA_RDY_REG)
#define UART_READ_REG(port)         (port? UART1_READ_REG : UART0_READ_REG)
#define UART_IRQ_ACK_REG(port)      (port? UART1_IRQ_ACK_REG : UART0_IRQ_ACK_REG)
#define UART_LIN_BREAK_REG(port)    (port? UART1_LIN_BREAK_REG : UART0_LIN_BREAK_REG)
#define UART_BRP_REG(port)          (port? UART1_BRP_REG : UART0_BRP_REG)

#define RT_UART_Off(port)             MemoryOr32(UART_CTL_REG(port),0x10)                  // UART off
#define RT_UART_On(port)              {MemoryAnd32(UART_CTL_REG(port),~0x10);}          // UART on
#define RT_UART_Busy(port)            MemoryRead32(UART_BUSY_REG(port))                // check tx busy
#define RT_UART_Write(port, val)      MemoryWrite32(UART_WRITE_REG(port),val)              // send the data
#define RT_UART_DataReady(port)       MemoryRead32(UART_DATA_RDY_REG(port))                // check data ready
#define RT_UART_Read(port)            MemoryRead32(UART_READ_REG(port))                  // read the data

#define RT_UART_IrqOn(port)         MemoryOr32(UART_CTL_REG(port),1)
#define RT_UART_IrqOff(port)        MemoryAnd32(UART_CTL_REG(port),~1)
/**
 * @brief This function sets UART1 compare irq on
 *
 * @return  void
 */
#define RT_UART_CompareOn(port)       MemoryOr32(UART_CTL_REG(port),0x2)                   // UART compare irq on
/**
 * @brief This function sets UART1 compare irq off
 *
 * @return  void
 */
#define RT_UART_CompareOff(port)      MemoryAnd32(UART_CTL_REG(port),~0x2)                 // UART compare irq off
/**
 * @brief This function sets UART1 compare value
 *
 * @return  void
 */
#define RT_UART_SetCompare(port, val)   MemoryOr32(UART_CTL_REG(port),val<<8)                // set irq compare bits
#define RT_UART_ClearIrq(port)        MemoryWrite32(UART_IRQ_ACK_REG(port),0x0)            // clear irq
#define RT_UART_RaiseIrq(port)        MemoryOr32(UART_CTL_REG(port),0x1)                   // raise irq manually
#define RT_UART_CheckIrq(port)        MemoryBitAt(UART_CTL_REG(port),0)                  // Check irq
// Set UART_Lin on
#define RT_UART_LinSyncOn(port)         MemoryOr32(UART_CTL_REG(port),0x8)               // auto Linsync on
// Set UART_Lin off
#define RT_UART_LinSyncOff(port)        MemoryAnd32(UART_CTL_REG(port),~0x8)             // auto Linsync off
// Set UART_Lin normal break
#define RT_UART_LinBreakNormal(port)    MemoryAnd32(UART_CTL_REG(port),~0x20)            // 13-bit Lin break
// Set UART_Lin extreme break
#define RT_UART_LinBreakExtreme(port)   MemoryOr32(UART_CTL_REG(port),0x20)              // 26-bit Lin break
// Set UART_Lin master send break
#define RT_UART_LinSendBreak(port)      MemoryWrite32(UART_LIN_BREAK_REG(port),0x0)      // send Lin break
// Check UART_Lin irq flag
#define RT_UART_LinCheckIrq(port)       ((MemoryRead32(UART_CTL_REG(port))&0x4)>>3)        // check Lin irq
// Get Brp value
#define RT_UART_GetBrp(port)            MemoryRead32(UART_BRP_REG(port))                 // get brp value
// Set UART_Lin Slave Mode
#define RT_UART_LinSlave(port)          UART_LinSyncOn()                       // Lin slave mode

void RT_UART_putchar(uint32_t port, unsigned char c);
void RT_UART_puts(uint32_t port, unsigned char *string);
unsigned char RT_UART_getchar(uint32_t port);
void RT_UART_LinMaster(uint32_t port, char pattern);
#endif
