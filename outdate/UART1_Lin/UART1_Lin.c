/**
* @file UART1_Lin.c
* @author Zhirui Dai
* @date 1 Nov 2017
* @copyright 2018 Zhirui
* @brief UART1 Lin Library for M2.
*/
#include "UART1_Lin.h"
/**
 * @brief This function sends out Lin signal when M2's uart1 works as Master
 *
 * @param pattern   Lin Break Pattern, NORMALBREAK or EXTREMEBREAK
 */
void RT_UART1_LinMaster(char pattern){
    RT_UART1_On();                             // UART1 on
    if(pattern) RT_UART1_LinBreakExtreme();    // pattern >=1, ExtremeBreak
    else    RT_UART1_LinBreakNormal();         // pattern ==0, NormalBreak
    RT_UART1_LinSendBreak();                   // send lin break frame
    while(RT_UART1_Busy());                    // check tx busy
    RT_UART1_Write(0x55);                      // send break syncing frame
}
