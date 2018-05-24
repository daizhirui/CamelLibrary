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
void UART_putchar(unsigned char c)
{
    while (UART_Busy())
        ;
    UART_Write(c);
}
/**
 * @brief This function sends a string by UART
 * 
 * @param string    the string to send
 */
void UART_puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            UART_putchar('\r');
        UART_putchar(*string++);
    }
}
/**
 * @brief This function returns 1-byte data from UART
 * 
 * @return unsigned char    1-byte data from UART
 */
unsigned char UART_getchar()
{
    while (!UART_DataReady())
        ;
    return UART_Read();
}