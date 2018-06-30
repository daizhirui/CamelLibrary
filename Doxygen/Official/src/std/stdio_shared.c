/**
 * @brief Standard Input Output Library For M2
 *
 * @file stdio.c
 * @author Zhirui
 * @date 2018-05-26
 */

#include <mcu.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

static char __convertBuffer[33];
static char __printfBuffer[128];

void _printf(char* buf, const char *format, va_list ap);


// Initialize a memory segment.
void _memset(char* ptr, unsigned int size, char value)
{
    while (size) {
        *ptr++ = value;
        size--;
    }
}

// connect src to the end of dest.
char * _strcat(char *dest, const char * src)
{
    char *ret = dest;
    while (*dest)
        dest++;
    while (*src){
        *(dest++) = *(src++);
    }
    return ret;
}

// calculate the length of str.
unsigned int _strlen(const char * str)
{
    register int n;
    n = 0;
    register char * tmp = (char *)str;
    while (*tmp) {
        n++;
        tmp++;
    }
    return n;
}

/**
 * @brief Print a character to uart0.
 *
 * @param c  Character to be printed.
 */
void putchar(char c)
{
    while(MemoryRead32(UART0_BUSY_REG)) {}
    MemoryWrite32(UART0_WRITE_REG, c);
}

/**
 * @brief Print a string to uart0.
 *
 * @param string  String to be printed.
 */
void puts(const char* string)
{
   while(*string)
   {
      if(*string == '\n')
         putchar('\r');
      putchar(*string++);
   }
}

/**
 * @brief Get a character from uart0.
 *
 * @return char  The character got from uart0.
 */
char getchar()
{
    while(!MemoryRead32(UART0_DATA_RDY_REG)) {}
    return MemoryRead32(UART0_READ_REG);
}

/**
 * @brief Get a decimal integer from uart0.
 *
 * @return long  The integer got from uart0.
 */
long getnum()
{
    register long i, value = 0;
    unsigned char ch;
    bool sign = false;
    for(i=0; i<10;) { // 2^32-1=4,294,967,295
        ch = getchar();
        if (ch == '\n' || ch == '\r' || ch == ' ') break;
        if ('0' <= ch && ch <= '9') ch -= '0';
        else if (ch == 8) {
            if (i > 0) --i;
            value /= 10;
            continue;
        }
        else if (ch == '-' && i == 0) {
            sign = true;
            continue;
        }
        value = value * 10 + ch;
        ++i;
    }
    if (sign) {
        value = -value;
    }
    return value;
}

/**
 * @brief Get a hexadecimal integer from uart0.
 *
 * @return unsigned long  An unsigned integer got from uart0.
 */
unsigned long getHexNum()
{
   int i;
   unsigned char ch;
   unsigned long value=0;

   for(i = 0; i < 16; )   // why 16 ? not 8?
   {
      ch  = getchar();
      if(ch == '\r')
         break;
      if(ch == '\n' || ch == '\r' || ch == ' ')
         break;
      if('0' <= ch && ch <= '9')
         ch -= '0';
      else if('A' <= ch && ch <= 'Z')
         ch = ch - 'A' + 10;
      else if('a' <= ch && ch <= 'z')
         ch = ch - 'a' + 10;
      else if(ch == 8)  // \b  backspace
      {
         if(i > 0)
            --i;
         value >>= 4;
         continue;
      }
      value = (value << 4) + ch;
      ++i;
   }
   return value;
}

/**
 * @brief Convert an integer to a string.
 *
 * @param value  Value to be converted to a string.
 * @param base  Numerical base used to represent the value as a string, between 2 and 36, where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
 * @return char*  A pointer to the resulting null-terminated string.
 */
char* itoa(int value, unsigned int base)
{
    char* start = __convertBuffer;
    char* end = __convertBuffer;
    char tmp;
    _memset(__convertBuffer,33,0);

    if (value < 0 && base == 10) {  // Check '-' sign.
        *(end++) = '-';
        start++;
        value = -value;
    }
    do {
        *end++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[value % base];
        value /= base;
    } while(value);
    *(end--) = '\0';                // end of a string.

    for (;end > start; ++start, --end) {    // Correct the order.
        tmp = *start;
        *start = *end;
        *end = tmp;
    }
    return __convertBuffer;
}

/**
 * @brief  Print a formated string to uart0.
 *
 * @param format  pointer to a null-terminated multibyte string specifying how to interpret the data.
 * @param ...   values to be interpreted.
 */
void printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    _printf(__printfBuffer, format, ap);
    va_end(ap);
    puts(__printfBuffer);
}

/**
 * @brief  Generate and store a formated string.
 *
 * @param buf  Buffer to store the string.
 * @param format  pointer to a null-terminated multibyte string specifying how to interpret the data.
 * @param ...  values to be interpreted.
 */
void sprintf(char* buf, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    _printf(buf, format, ap);
    va_end(ap);
}
