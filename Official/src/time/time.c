/**
* @file time.c
* @author Zhirui Dai
* @date 16 Jun 2018
* @copyright 2018 Zhirui
* @brief Real Time Module Library for M2
*/
#include "mcu.h"
#include "time.h"

void RT_RTC_GetTime(unsigned char *d_year,unsigned char *d_mon,unsigned char *d_day,
                unsigned char *d_hour,unsigned char *d_min,unsigned char *d_sec)
{
    unsigned long time;
    time = RT_RTC_Read32();
    if (d_year != 0)
        *d_year =(unsigned char)((time>>26)&0x3f);         // read d_year, [31,26], 6bits
    if (d_mon != 0)
        *d_mon = (unsigned char)((time>>22)&0x0f);       // read d_mon, [25,22], 4bits
    if (d_day != 0)
        *d_day = (unsigned char)((time>>17)&0x1f);         // read d_day, [21,17], 5bits
    if (d_hour != 0)
        *d_hour = (unsigned char)((time>>12)&0x1f);        // read d_hour, [16,12], 5bits
    if (d_min != 0)
        *d_min = (unsigned char)((time>>6)&0x3f);       // read d_min, [11,6], 6bits
    if (d_sec != 0)
        *d_sec = (unsigned char)(time&0x3f);            // read d_sec, [5,0], 6bits
}

void RT_DelayMiliseconds(unsigned long ms)
{
    unsigned int i;
    while(ms--)
    {
        for (i = 0; i < 200; i++)
            __asm__("nop");
    }
}
