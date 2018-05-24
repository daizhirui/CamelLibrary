/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: Zhirui Dai
 * DATE CREATED: 2017/11/1
 * DATE MODIFIED: 2018/04/30
 * FILENAME: extend_str.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 *      This Library is an extension of str library.
 * 2018/04/30: fix a bug of num2Dec
 *--------------------------------------------------------------------*/
#include "UART0.h"
#include "str.h"
#include "extend_str.h"
/*  This function is definded as putch in str library.
void putchar(unsigned char c)
{
    while (uart0_Busy())
        ;
    uart0_Write(c);
}*/

/*  This function is already defined in str library.
void puts(unsigned char *string)
{
    while (*string)
    {
        if (*string == '\n')
            putchar('\r');
        putchar(*string++);
    }
}*/

/*  This function is definded as getch in str library.
unsigned char getchar()
{
    while (!uart0_DataReady())
        ;
    return uart0_Read();
}*/

/*  This function is definded as getnum in str library.
unsigned long getHexNum(void)
{
    register int i;
    register unsigned char ch;
    register unsigned long value = 0;

    for (i = 0; i < 8;) // it was 16 before, I think it should be 8
    {
        ch = getchar();
        if (ch == '\r')
            break;
        if (ch == '\n' || ch == '\r' || ch == ' ')
            break;
        if ('0' <= ch && ch <= '9')
            ch -= '0';
        else if ('A' <= ch && ch <= 'Z')
            ch = ch - 'A' + 10;
        else if ('a' <= ch && ch <= 'z')
            ch = ch - 'a' + 10;
        else if (ch == 8) // ^H  or \b  backspace  ???
        {
            if (i > 0)
                --i;
            value >>= 4;
            continue;
        }
        value = (value << 4) + ch;
        ++i;
    }
    return value;
}*/
/**
 * @brief
 * This function converts a string in decimal style to a long type number.
 * @param void
 * @return unsigned long    the decimal number
 */
unsigned long getDecNum(void)
{
    register int i;
    register unsigned char ch;
    register unsigned long value = 0;
    for (i = 0; i < 10;) // 2^32-1=4,294,967,295
    {
        ch = getchar();
        if (ch == '\r')
            break;
        if (ch == '\n' || ch == '\r' || ch == ' ')
            break;
        if ('0' <= ch && ch <= '9')
            ch -= '0';
        else if (ch == 8) // ^H  or \b  backspace  ???
        {
            if (i > 0)
                --i;
            value /= 10;
            continue;
        }
        value = value * 10 + ch;
        ++i;
    }
    return value;
}
/* This function is definded as xtoa in str library.
char *num2Hex(unsigned long num)
{
    static char buf[12];
    register int i, digit; // advise compiler store i and digit in register
    buf[8] = 0;
    for (i = 7; i >= 0; --i)
    {
        digit = num & 0xf;
        buf[i] = digit + (digit < 10 ? '0' : 'A' - 10);
        num >>= 4;
    }
    return buf;
}*/
/**
 * @brief
 * This function converts a number to a string in decimal style.
 * @param num       The number to be converted
 * @return char*    The pointer to the result
 */
char* num2Dec(long num)
{
    static char buf[15];             // to store the decimal result
    register char i, index = 1;      // i is the index of buf, index is the length of the decimal result.
    register unsigned long opt = 10; // used to get the number of every position
    if ((num & 0x80000000) >> 31) {                   // check if num is negative
        buf[0] = '-';     // store the negative sign
        num = -num; // num = -num
        i = 1;            // move the index of buf
        index++;          // increase the length of the decimal result
    }
    else {
        i = 0;
    }
    while (opt <= num)
    { // calculate the length of the decimal result
        opt *= 10;
        index++;
    }
    opt /= 10;
    for (; i < index; i++)
    { // get every number
        buf[i] = num / opt;
        num = num - buf[i] * opt;
        buf[i] += '0';
        opt /= 10;
    }
    buf[index] = '\0'; // string end sign
    return buf;
}
/**
 * @brief
 * This function converts a number to a string in bin style.
 * @param num       The number to be converted
 * @return char*    The pointer to the result
 */
char *num2Bin(unsigned long num)
{
    static char buf[33];
    register char i;
    for (i = 0; i < 32; i++)
    {
        buf[31 - i] = (num >> i) & 0x1 + '0'; // get every number
    }
    buf[32] = '\0';
    return buf;
}

unsigned int Hex2num(char *string)
{
    int i=0;
    while(*string)  // when reaching to the end of string, it's 0 and will exit.
    {
        i <<= 4;    // left shift 4 bits
        if('0' <= *string && *string <= '9')
            i += *string - '0';
        if('A' <= *string && *string <='Z')
            i += *string - 'A' + 10;
        if('a' <= *string && *string <= 'z')
            i += *string - 'a' + 10;
        else
            break;  // meet NOT HEX sign, exit
        string++;
    }
    return i;
}
unsigned int Dec2num(char *string)
{
    int i=0;
    while(*string)
    {
        i = i*10;
        if('0' <= *string && *string <= '9')
            i += *string - '0';
        else
            break;  // meet NOT DEC sign, exit.
        string++;
    }
    return i;
}
