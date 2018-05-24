/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Astro
 * DATE CREATED: 2017/11/1
 * FILENAME: UART0_Lin.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *--------------------------------------------------------------------*/
#include "UART0_Lin.h"
/**
 * @brief This function sends out Lin signal when M2's uart0 works as Master
 * 
 * @param pattern   Lin Break Pattern, NORMALBREAK or EXTREMEBREAK
 */
void UART0_LinMaster(char pattern){
    UART0_On();                             // UART1 on
    if(pattern) UART0_LinBreakExtreme();    // pattern >=1, ExtremeBreak
    else    UART0_LinBreakNormal();         // pattern ==0, NormalBreak
    UART0_LinSendBreak();                   // send lin break frame
    while(UART0_Busy());                    // check tx busy
    UART0_Write(0x55);                      // send break syncing frame
}
