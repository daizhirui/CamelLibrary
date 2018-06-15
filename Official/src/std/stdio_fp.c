/**
 * @brief Standard Input Output Library For M2
 *
 * @file stdio_fp.c
 * @author Zhirui
 * @date 2018-05-26
 */

#include <stdarg.h>
#include <soft_fp.h>
#include <stdio_fp.h>
#include "stdio_shared.c"

/**
 * @brief Convert a float value to a string.
 *
 * @param a_fp  Value to be converted to a string.
 * @return char*  A pointer to the resulting null-terminated string.
 */
char* ftoa(float a_fp)
{
    static char buf[33];
    _memset(buf,33,0);
    if (a_fp < 1.0f) {
        unsigned char pos = 0;
        if ((*(unsigned long*)&(a_fp))&0x80000000) { // check sign
            buf[0] = '-';
            buf[1] = '0';
            buf[2] = '.';
            pos = 3;
        } else {
            buf[0] = '0';
            buf[1] = '.';
            pos = 2;
        }

        while((a_fp *= 10) < 1) {   // find a none 0 beginning
            buf[pos++] = '0';
        }
        a_fp *= 10000;
        int frac_part = fp_float32_to_int32(a_fp);
        itoa(frac_part, 10);
        _strcat(buf, __convertBuffer);
        return buf;
    } else {
        long integer_part = fp_float32_to_int32(a_fp);
        itoa(integer_part, 10);
        _strcat(buf,__convertBuffer);
        _strcat(buf, ".");               //append decimal point
        a_fp = abs(a_fp);
        int frac_part = (a_fp - fp_int32_to_float32(integer_part)) * 100000;  //subtract to get the decimals, and multiply by 1000
        itoa(frac_part, 10);                     //convert to a second string
        _strcat(buf, __convertBuffer);          //and append to the first
        return buf;
    }
}

void _printf(char* buf, const char *format, va_list ap)
{
    _memset(buf, 128, '\0');
    for(; *format; ++format) {
        if (*format != '%') {
            *(buf++) = *format;
        } else {
            ++format;
            switch (*format) {
                case 'd': {
                    itoa(va_arg(ap, int), 10);
                    _strcat(buf, __convertBuffer);
                    buf += _strlen(buf);
                    // ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'X':
                case 'x': {
                    itoa(va_arg(ap, int), 16);
                    buf += _strlen(buf);
                    // ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'c': {
                    *(buf++) = (char)va_arg(ap, int);
                    // ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'f': {
                    char* float_str = ftoa(va_arg(ap, double));
                    _strcat(buf, float_str);
                    buf += _strlen(buf);
                    break;
                }
                case 's': {
                    _strcat(buf, va_arg(ap, char*));
                    buf += _strlen(buf);
                    // ap = va_next(ap, char*); // move to next param
                    break;
                }
                default: {
                    *(buf++) = '%';
                    *(buf++) = *format;
                    break;
                }
            } // End of switch
        } // End of if-else
    } // End of for
} // End of _printf
