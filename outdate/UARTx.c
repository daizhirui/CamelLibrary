/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/5
 * FILENAME: UARTx.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *      Since M2 has 2 UART, it will be more efficient and more flexible
 * to use UARTx library instead of UART0 or UART1.
 *      When users use UARTx library, they only need to change the global
 * value UARTPORT to choose the UART they want to use.
 *--------------------------------------------------------------------*/
/**
 * @brief This function sends 1-byte data by UART
 *
 * @param c     1-byte data to send
 */
#include "UARTx.h"
void RT_UART_putchar(unsigned char c)
{
    while (RT_UART_Busy())
        ;
    RT_UART_Write(c);
}
/**
 * @brief This function sends a string by UART
 *
 * @param string    the string to send
 */
void RT_UART_puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            RT_UART_putchar('\r');
        RT_UART_putchar(*string++);
    }
}
/* Function: RT_UART_getchar
 */
unsigned char RT_UART_getchar()
{
    while (!RT_UART_DataReady())
        ;
    return RT_UART_Read();
}
