# UART Library for M2

UART library provides interface to operate UART0 and UART1 of M2.

## Interface

```C
void RT_UART_On(port);

void RT_UART_Off(port);

void RT_UART_Busy(port);

void RT_UART_Write(port);

uint32_t RT_UART_DataReady(port);

uint8_t RT_UART_Read(port);

void RT_UART_IrqOn(port);

void RT_UART_CompareOn(port);

void RT_UART_CompareOff(port);

void RT_UART_SetCompare(port, val);

void RT_UART_ClearIrq(port);

void RT_UART_RaiseIrq(port);

void RT_UART_CheckIrq(port);

void RT_UART_LinSyncOn(port);

void RT_UART_LinSyncOff(port);

void RT_UART_LinBreakNormal(port);

void RT_UART_LinBreakExtreme(port);

void RT_UART_LinSendBreak(port);

void RT_UART_LinCheckIrq(port);

uint32_t RT_UART_GetBrp(port);

void RT_UART_LinSlave(port);

void RT_UART_putchar(uint32_t port, unsigned char c);

void RT_UART_puts(uint32_t port, unsigned char *string);

unsigned char RT_UART_getchar(uint32_t port);

void RT_UART_LinMaster(uint32_t port, char pattern);
```

## Example

### Send and receive data via UART0 and UART1

```C
/*
 * Before running this example, please connect pins:
 *      P_TX <------> SPI_SI/RX1
 *      P_RX <------> SPI_SO/TX1  
 */
#include "UART.h"

void user_interrupt(){}

int main() {
    char c;

    // Turn on UART0 and UART1
    RT_UART_On(UART0);
    RT_UART_On(UART1);

    while(1) {
        c = RT_UART_getchar(UART1);
        RT_UART_puts(UART0, "Get a character from UART1: ");
        RT_UART_putchar(UART0, c);
        RT_UART_putchar(UART0, '\n');
    }
}
```

### Send Lin break via UART1

```C
#include "UART.h"

void user_interrupt()

int main() {
    RT_UART_On(UART1);                          // Turn on UART1
    // RT_UART_LinSlave(UART1);                 // set M2 as Lin slave
    // RT_UART_LinMaster(UART1, NORMAL_BREAK);  // 13-bit break
    RT_UART_LinMaster(UART1, EXTREME_BREAK);    // 26-bit break
    // ATTENTION: When RT_UART_LinMaster is used, a break will be sent automatically.
    RT_UART_LinSendBreak(UART1);                // Send break again manually.

    // code after Lin sync
    // ...
}
```
