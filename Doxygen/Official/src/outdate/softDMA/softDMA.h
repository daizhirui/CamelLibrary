/**
* @file softDMA.h
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief Soft Direct Memory Access(DMA) Controller
*/

#include <stdint.h>
#include <stdbool.h>

#ifndef __SOFT_DMA_H__
#define __SOFT_DMA_H__

typedef struct {
    uint8_t* buffer;
    uint8_t bufferSize;
    uint8_t* usage;
} DMA;

typedef struct {
    DMA* dmaDevice[2];
    uint8_t deviceEnabled[2];
    uint8_t timeout;
} DMA_Controller;
/**
 * @brief   Store data from uart.
 */
DMA_Controller dmaController;

void SoftDMA_init(uint8_t timeout);
void SoftDMA_registerDMA(DMA* device, uint8_t port);
void SoftDMA_turnOnController();
void SoftDMA_turnOffController();
void SoftDMA_enableDevice(uint8_t port);
void SoftDMA_disableDevice(uint8_t port);
void SoftDMA_updateUsage(uint8_t port, uint8_t newUsage);

#endif
