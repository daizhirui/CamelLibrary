/**
* @file TC0.c
* @author Zhirui Dai
* @date 11 Jul 2018
* @copyright 2018 Zhirui
* @brief Timer Counter 0 Library for M2
*/

#include "TC0.h"

inline void RT_TC0_TimerSet1us(uint32_t T, switch_t irqEn)
{
    // [T0_CLK_REG] = 3 * T / [T0_REF_REG] - 1
    // Let [T0_REF_REG] = 255, get [T0_CLK_REG]
    uint32_t clk = T / 81 - 1;
    if (clk < 1) clk = 1;
    uint32_t ref = 30 * T / clk;
    if (ref % 10 >= 5) ref = ref / 10 + 1;  // ensure the interval is bigger than T
    else ref /= 10;
    MemoryAnd32(T0_CTL0_REG, ~(1 << 7));    // turn off irq
    MemoryWrite32(T0_CLK_REG, clk);
    MemoryWrite32(T0_REF_REG, ref);
    MemoryOr32(T0_CTL0_REG, (0x02 | (irqEn << 7)));
    MemoryOr32(SYS_CTL0_REG, irqEn);
}
