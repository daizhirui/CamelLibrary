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
#include <stdio_shared.h>

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
    *buf = '\0';
}
