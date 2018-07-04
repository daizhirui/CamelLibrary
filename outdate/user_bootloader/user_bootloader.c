#include <stdio.h>
#include "user_bootloader.h"
#include "Interrupt.h"
#include "UART0.h"
#include "mcu.h"

#define UPDATE_SIGNAL   255
#define USER_INTERRUPT2_ADDRESS 0x10000008

void sys_init()
{
    RT_SYSINT_On();
    // RT_UART0_IrqOn();   // Enable U
    RT_UART0_SetCompare(UPDATE_SIGNAL);
    RT_UART0_CompareOn();
}

void user_interrupt(void)
{
    // check update message
    if (RT_UART0_CheckIrq()) {
        if (RT_UART0_Read() == UPDATE_SIGNAL) {
            
        }
    }
    // jump to user's interrupt
    FuncPtr user_interrupt2 = (FuncPtr)USER_INTERRUPT2_ADDRESS;
    user_interrupt2();
}

int main(void)
{
    sys_init();
}
