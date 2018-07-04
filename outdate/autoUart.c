/**
 * @brief Functions for UART0, UART1...
 *
 * @file autoUART.c
 * @author Zhirui Dai
 * @date 2018-05-28
 */

#include "mcu.h"
#include "UART0.h"
#include "autoUart.h"

#define UART_NUM    2
#define RT_UARTx_IrqOn(port)            MemoryOr32(UART0_CTL_REG|port<<11,1)
#define RT_UARTx_IrqOff(port)           MemoryAnd32(UART0_CTL_REG|port<<11,~1)
#define RT_UARTx_CheckIrq(port)         MemoryBitAt(UART0_CTL_REG|port<<11,0)
#define RT_UARTx_ClearIrq(port)         MemoryWrite32(UART0_IRQ_ACK_REG|port<<11,0x0)
#define RT_UARTx_DataReady(port)        MemoryRead32(UART0_DATA_RDY_REG|port<<11)
#define RT_UARTx_Read(port)             MemoryRead32(UART0_READ_REG|port<<11)
#define RT_UARTx_SetCompare(port,val)   MemoryOr32(UART0_CTL_REG|port<<11,val<<8)
#define RT_UARTx_CompareOn(port)        MemoryOr32(UART0_CTL_REG|port<<11,0x2)
#define RT_UARTx_CompareOff(port)       MemoryAnd32(UART0_CTL_REG|port<<11,~0x2)

void user_interrupt(void);
void interrupt(void) {
    MemoryWrite(USER_INT, 0x1);

    if (__autoUartEnabled && RT_UARTx_CheckIrq(__uartPort)) {        // autoUART is enabled
        unsigned int timeout = __uartTimeout;
        unsigned char data;
        while(timeout) {
            if (RT_UARTx_DataReady(__uartPort)) {
                data = RT_UARTx_Read(__uartPort);              // Get the data.
                __uartBuffer[__uartBufferIndex] = data;
                __uartBufferIndex++;     // Update index.
                if ((__uartTerminal != NULL && data == *__uartTerminal)\
                ||(__uartBufferIndex == __uartBufferSize - 1)\
                ||(__uartTerminal == NULL && data == '\0')) {      // CHeck terminal.
                    __uartBuffer[__uartBufferIndex] = '\0';
                    __autoUartDataReady = true;
                    break;
                }
                timeout+=10;    // One successful receving makes it wait for longer time.
            } else {
                timeout--;
            }
        }
        if (__autoUartUserHandler) {
            __autoUartUserHandler();      // Execute the handler if it is not NULL.
        }
        RT_UARTx_ClearIrq(__uartPort);    // clear irq.
    }

    user_interrupt();
}

void RT_AUTOUART_Enable(unsigned char port, unsigned char* buffer, unsigned char bufferSize,\
                        char* start, char* terminal, unsigned int timeout, FuncPtr handler)
{
    if (port >= UART_NUM) { // Check if port is correct.
        return;
    }
    if (buffer == NULL) {   // Check if a buffer is provided.
        return;
    }
    if (bufferSize < 2) {   // Check if the size of the buffer meets the standard: null-terminated string containing at least one character.
        return;
    }

    __uartPort = port;
    __uartBuffer = buffer;          // Load the buffer.
    __uartBufferSize = bufferSize;  // Load the bufferSize.
    __uartTerminal = terminal;      // Load the terminal.
    __uartTimeout = timeout;        // Load the timeout.
    __uartBufferIndex = 0;          // Initialize the index.
    __autoUartEnabled = true;       // autoUart enabled.
    __autoUartDataReady = false;    // data not ready yet.

    if (start!=NULL) {
        RT_UARTx_SetCompare(port,*start);
        RT_UARTx_CompareOn(port);
    } else {
        RT_UARTx_CompareOff(port);
    }

    if (handler != NULL) {
        __autoUartUserHandler = handler;
    } else {
        __autoUartUserHandler = NULL;
    }

    RT_UARTx_IrqOn(port);       // Enable uart interrupt
    RT_UARTx_ClearIrq(port);    // Clear uart interrupt
    RT_SYSINT_En();         // Enable system interrupt.
}

void RT_AUTOUART_Disabled()
{
    RT_UARTx_IrqOff(__uartPort);
    RT_SYSINT_Off();
    __autoUartEnabled = false;
}
