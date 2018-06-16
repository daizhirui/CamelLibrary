/**
 * @file softDMA.c
 * @author Zhirui Dai
 * @date 16 Jun 2018
 * @copyright 2018 Zhirui
 * @brief Soft Direct Memory Access(DMA) Controller
 */

#include "softDMA.h"
#include "Interrupt.h"
#include "stdio.h"
#include "UART0.h"
#include "UART1.h"
#define NULL 0x0

void user_interrupt(void);  // This function should be defined by user.

inline void SoftDMA_init(uint8_t timeout)
{
    dmaController.dmaDevice[0] = NULL;
    dmaController.dmaDevice[1] = NULL;
    dmaController.deviceEnabled[0] = false;
    dmaController.deviceEnabled[1] = false;
    dmaController.timeout = timeout;
}

inline void SoftDMA_registerDMA(DMA* device, uint8_t port)
{
    if (device->buffer == NULL || device->bufferSize == 0 || device->usage == NULL) {
        return;
    }
    dmaController.dmaDevice[port] = device;
    *(device->usage) = 0;
}

inline void SoftDMA_turnOnController()
{
    if (dmaController.dmaDevice[0] != NULL && dmaController.deviceEnabled[0]) {
        RT_UART0_IrqOn();
    }
    if (dmaController.dmaDevice[1] != NULL && dmaController.deviceEnabled[1]) {
        RT_UART1_IrqOn();
    }
    RT_SYSINT_On();
}

inline void SoftDMA_turnOffController()
{
    if (dmaController.dmaDevice[0] != NULL && dmaController.deviceEnabled[0]) {
        RT_UART0_IrqOff();
    }
    if (dmaController.dmaDevice[1] != NULL && dmaController.deviceEnabled[1]) {
        RT_UART1_IrqOff();
    }
    RT_SYSINT_Off();
}

inline void SoftDMA_enableDevice(uint8_t port)
{
    dmaController.deviceEnabled[port] = true;
}

inline void SoftDMA_disableDevice(uint8_t port)
{
    dmaController.deviceEnabled[port] = false;
}
/**
 * @brief   An interrupt function invocked when dmaController is enabled.
 */
void before_user_interrupt()    // override void before_user_interrupt(void) in m2core
{
    // check if dmaDevice of uart0 is enabled.
    uint8_t timeout = dmaController.timeout;
    uint8_t* pos;
    if (dmaController.dmaDevice[0] != NULL && dmaController.deviceEnabled[0]) {
        if (RT_SYSINT_Flag(SYSINT_UART0INT)) {  // check irq flag of uart0
            while(timeout) {
                if (RT_UART0_DataReady()) { // make sure the data is ready.
                    pos = dmaController.dmaDevice[0]->usage;
                    *pos %= dmaController.dmaDevice[0]->bufferSize; // avoid index overflow
                    dmaController.dmaDevice[0]->buffer[*pos] = RT_UART0_Read();
                    *pos = *pos + 1;
                } else {
                    timeout--;
                }
            }
            dmaController.dmaDevice[0]->buffer[*pos] = 0;
            RT_UART1_ClearIrq();    // clear irq flag of uart1
        }
    }
    // check if dmaDevice of uart1 is enabled.
    timeout = dmaController.timeout;
    if (dmaController.dmaDevice[1] != NULL && dmaController.deviceEnabled[1]) {
        if (RT_SYSINT_Flag(SYSINT_UART1INT)) {  // check irq flag of uart1
            while(timeout) {
                if (RT_UART1_DataReady()) { // make sure the data is ready.
                    uint8_t* pos = dmaController.dmaDevice[1]->usage;
                    *pos %= dmaController.dmaDevice[1]->bufferSize; // avoid index overflow
                    dmaController.dmaDevice[1]->buffer[*pos] = RT_UART1_Read();
                    *pos = *pos + 1;
                } else {
                    timeout--;
                }
            }
            dmaController.dmaDevice[0]->buffer[*pos] = 0;
            RT_UART1_ClearIrq();    // clear irq flag of uart1
        }
    }
    user_interrupt();
}

inline void SoftDMA_updateUsage(uint8_t port, uint8_t newUsage)
{
    if (dmaController.dmaDevice[port] != NULL) {    // check if dmaDevice exists.
        *(dmaController.dmaDevice[port]->usage) = newUsage;
    }
}
