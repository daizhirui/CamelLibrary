/**
 * @brief Standard Input Output Library For M2
 *
 * @file stdio.c
 * @author Zhirui
 * @date 2018-05-26
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include "stdio_shared.c"

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
                    _strcat(buf, __convertBuffer);
                    buf += _strlen(buf);
                    ap = va_next(ap, int); // move to next param
                    break;
                }
                case 'c': {
                    *(buf++) = va_arg(ap, char);
                    ap = va_next(ap, char); // move to next param
                    break;
                }
                case 'f': {
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
