/**
* @file stdlib.c
* @author Zhirui Dai
* @date 27 May 2018
* @copyright 2018 Zhirui
* @brief Standard Library for M2
*/
#ifndef __M2_STDLIB_H__
#define __M2_STDLIB_H__

#include <stdbool.h>

/**
 * @brief Convert a string (hexadecimal) to an integer value.
 *
 * @param str  String (hexadecimal) to be converted to an integer.
 * @return unsigned long  An unsigned long integer.
 */
unsigned long xtoi(const char* str)
{
    int value = 0;
    while(*str) { // when reaching to the end of str, it's 0 and will exit.
        value <<= 4;    // left shift 4 bits
        if('0' <= *str && *str <= '9')
            value += *str - '0';
        if('A' <= *str && *str <='Z')
            value += *str - 'A' + 10;
        if('a' <= *str && *str <= 'z')
            value += *str - 'a' + 10;
        else
            break;  // meet NOT HEX sign, exit
        str++;
    }
    return value;
}

/**
 * @brief Convert a string (decimal) to an integer value.
 *
 * @param str  String (decimal) to be converted to an integer.
 * @return long  A long integer.
 */
long atoi(const char* str)
{
    bool sign = false;
    long value = 0;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    while(*str) {
        value = value * 10;
        if('0' <= *str && *str <= '9')
            value += *str - '0';
        else
            break;  // meet NOT DEC sign, exit.
        str++;
    }
    if (sign) {
        value = -value;
    }
    return value;
}

#endif  // End of __M2_STDLIB_H__
