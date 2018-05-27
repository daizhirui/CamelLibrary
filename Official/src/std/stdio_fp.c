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
#include <stdio_shared.h>

/**
 * @brief Convert a float value to a string.
 * 
 * @param a_fp  Value to be converted to a string.
 * @return char*  A pointer to the resulting null-terminated string.
 */
char* ftoa(float a_fp)
{
    itoa((int)a_fp, 10);
    _strcat(buf, ".");               //append decimal point
    a_fp = FP_Abs(a_fp);
    int i = (a_fp - (int)a_fp) * 1000000;  //subtract to get the decimals, and multiply by 1000
    char frac_part[4];
    itoa(i, 10);                     //convert to a second string
    _strcat(buf, frac_part);          //and append to the first
    return buf;
}

void _printf(char* buf, const char *format, va_list ap)
{
    for(; *format; ++format) {
        if (*format != '%') {
            *(buf++) = *format;
        } else {
            ++format;
            switch (*format) {
                case 'd': {
                    itoa(va_arg(ap, int), 10);
                    buf += _strlen(buf);
                    break;
                }
                case 'X':
                case 'x': {
                    itoa(va_arg(ap, int), 16);
                    buf += _strlen(buf);
                    break;
                }
                case 'c': *(buf++) = va_arg(ap, char); break;
                case 'f': {
                    ftoa(va_arg(ap, float));
                    buf += _strlen(buf);
                    break;
                }
                case 's': {
                    _strcat(buf, va_arg(ap, char*));
                    buf += _strlen(buf);
                    break;
                }
                default: {
                    *(buf++) = '%';
                    *(buf++) = *format;
                    break;
                }
            }
        }
    }
}
