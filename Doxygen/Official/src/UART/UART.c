/**
* @file UART.c
* @author Zhirui Dai
* @date 1 Nov 2017
* @copyright 2018 Zhirui
* @brief UART Library for M2
*/

#include "UART.h"

void RT_UART_putchar(uint32_t port, unsigned char c)
{
    while (RT_UART_Busy(port))
        ;
    RT_UART_Write(port, c);
}

void RT_UART_puts(uint32_t port, unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            RT_UART_putchar(port, '\r');
        RT_UART_putchar(port, *string++);
    }
}

unsigned char RT_UART_getchar(uint32_t port)
{
    while (!RT_UART_DataReady(port))
        ;
    return RT_UART_Read(port);
}

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
