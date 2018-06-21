/**
* @file UART.c
* @author Zhirui Dai
* @date 1 Nov 2017
* @copyright 2018 Zhirui
* @brief UART Library for M2
*/

#include "UART.h"

/**
 * @brief This function sends 1-byte data by UART
 * @param port  UART port to use, optional value: \code{.c}UART0, UART1\endcode
 * @param c     1-byte data to send
 */
void RT_UART_putchar(uint32_t port, unsigned char c)
{
    while (RT_UART_Busy(port))
        ;
    RT_UART_Write(port, c);
}
/**
 * @brief This function sends a string by UART
 * @param port  UART port to use, optional value: \code{.c}UART0, UART1\endcode
 * @param string    the string to send
 */
void RT_UART_puts(uint32_t port, unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            RT_UART_putchar(port, '\r');
        RT_UART_putchar(port, *string++);
    }
}
/**
 * @brief This function returns 1-byte data from UART
 * @param port  UART port to use, optional value: \code{.c}UART0, UART1\endcode
 * @return unsigned char    1-byte data from UART
 */
unsigned char RT_UART_getchar(uint32_t port)
{
    while (!RT_UART_DataReady(port))
        ;
    return RT_UART_Read(port);
}
/**
 * @brief This function sends out Lin signal when M2's UART works as Master
 * @param port  UART port to use, optional value: \code{.c}UART0, UART1\endcode
 * @param pattern   Lin Break Pattern, NORMALBREAK or EXTREMEBREAK
 */
void RT_UART_LinMaster(uint32_t port, char pattern){
    RT_UART_On(port);                             // UART1 on
    if(pattern)
        RT_UART_LinBreakExtreme(port);    // pattern >=1, ExtremeBreak
    else
        RT_UART_LinBreakNormal(port);     // pattern ==0, NormalBreak
    RT_UART_LinSendBreak(port);           // send lin break frame
    while(RT_UART_Busy(port));            // check tx busy
    RT_UART_Write(port, 0x55);            // send break syncing frame
}
