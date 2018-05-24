/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/1
 * FILENAME: UART0.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *--------------------------------------------------------------------*/
/**
 * @brief This function sends 1-byte data by UART0
 * 
 * @param c     1-byte data to send
 */
#include "UART0.h"
void UART0_putchar(unsigned char c)
{
    while (UART0_Busy())
        ;
    UART0_Write(c);
}
/**
 * @brief This function sends a string by UART0
 * 
 * @param string    the string to send
 */
void UART0_puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            UART0_putchar('\r');
        UART0_putchar(*string++);
    }
}
/**
 * @brief This function returns 1-byte data from UART0
 * 
 * @return unsigned char    1-byte data from UART0
 */
unsigned char UART0_getchar()
{
    while (!UART0_DataReady())
        ;
    return UART0_Read();
}