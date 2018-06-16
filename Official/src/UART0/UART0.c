/**
* @file UART0.c
* @author Zhirui Dai
* @date 1 Nov 2017
* @copyright 2018 Zhirui
* @brief UART0 Library for M2
*/

#include "UART0.h"

/**
 * @brief This function sends 1-byte data by UART0
 *
 * @param c     1-byte data to send
 */
void RT_UART0_putchar(unsigned char c)
{
    while (RT_UART0_Busy())
        ;
    RT_UART0_Write(c);
}
/**
 * @brief This function sends a string by UART0
 *
 * @param string    the string to send
 */
void RT_UART0_puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            RT_UART0_putchar('\r');
        RT_UART0_putchar(*string++);
    }
}
/**
 * @brief This function returns 1-byte data from UART0
 *
 * @return unsigned char    1-byte data from UART0
 */
unsigned char RT_UART0_getchar()
{
    while (!RT_UART0_DataReady())
        ;
    return RT_UART0_Read();
}
