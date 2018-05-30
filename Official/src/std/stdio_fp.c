/**
 * @brief Standard Input Output Library For M2
 *
 * @file stdio_fp.c
 * @author Zhirui
 * @date 2018-05-26
 */

#include <stdarg.h>
#include <stddef.h>
#include <math.h>
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
    itoa((int)a_fp, 10);
    _strcat(__convertBuffer, ".");               //append decimal point
    a_fp = FP_Abs(a_fp);
    int i = (a_fp - (int)a_fp) * 1000000;  //subtract to get the decimals, and multiply by 1000
    char frac_part[4];
    itoa(i, 10);                     //convert to a second string
    _strcat(__convertBuffer, frac_part);          //and append to the first
    return __convertBuffer;
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
                    ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'X':
                case 'x': {
                    itoa(va_arg(ap, int), 16);
                    buf += _strlen(buf);
                    ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'c': {
                    *(buf++) = va_arg(ap, char);
                    ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'f': {
                    ftoa(va_arg(ap, float));
                    buf += _strlen(buf);
                    break;
                }
                case 's': {
                    _strcat(buf, va_arg(ap, char*));
                    buf += _strlen(buf);
                    ap = va_next(ap, char*); // move to next param
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
