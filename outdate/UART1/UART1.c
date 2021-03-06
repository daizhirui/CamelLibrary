/**
* @file UART1.c
* @author Zhirui Dai
* @date 1 Nov 2017
* @copyright 2018 Zhirui
* @brief Uart1 Library for M2
*/
#include "UART1.h"

/**
 * @brief This function sends 1-byte data by UART1
 *
 * @param c     1-byte data to send
 */
void RT_UART1_putchar(unsigned char c)
{
    while (RT_UART1_Busy())
        ;
    RT_UART1_Write(c);
}
/**
 * @brief This function sends a string by UART1
 *
 * @param string    the string to send
 */
void RT_UART1_puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            RT_UART1_putchar('\r');
        RT_UART1_putchar(*string++);
    }
}
/**
 * @brief This function returns 1-byte data from UART1
 *
 * @return unsigned char    1-byte data from UART0
 */
unsigned char RT_UART1_getchar()
{
    while (!RT_UART1_DataReady())
        ;
    return RT_UART1_Read();
}
