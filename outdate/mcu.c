char* xtoa(unsigned long num)
{
   static char buf[12];
   int i, digit;
   buf[8] = 0;
   for (i = 7; i >= 0; --i)
   {
      digit = num & 0xf;
      buf[i] = digit + (digit < 10 ? '0' : 'A' - 10);
      num >>= 4;
   }
   return buf;
}


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


/**
 * @brief      Convert Hex string to unsigned int.
 *
 * @param      string  The Hex String.
 *
 * @return     An unsigned int expressed by the string.
 */
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

/**
 * @brief      Convert Dec string to unsigned int.
 *
 * @param      string  The Dec string.
 *
 * @return     An unsigned int expressed by the string.
 */
int Dec2num(char *string)
{
    int sign = 1;
    int i=0;
    if (*string == '-')
    {
        sign = -1;
        string++;
    }
    while(*string)
    {
        i = i*10;
        if('0' <= *string && *string <= '9')
            i += *string - '0';
        else
            break;  // meet NOT DEC sign, exit.
        string++;
    }
    return i * sign;
}
