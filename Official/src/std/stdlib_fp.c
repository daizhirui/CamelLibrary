/**
 * @brief Standard Library for M2
 * 
 * @file stdlib.c
 * @author Zhirui Dai
 * @date 2018-05-27
 */

#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <stdlib_fp.h>

/**
 * @brief Convert a string (decimal) to a float value.
 * 
 * @param str  String (decimal) to be converted to a float value.
 * @return float  A float value.
 */
float atof(char* str)
{
    float value;
    int integer;
    int fraction;
    char* frac = str;
    while( *frac != '.' ) { // find the fraction part.
        frac++;
    }
    frac++;
    integer = atoi(str);
    *(frac + 6) = '\0';
    fraction = atoi(str);
    value = integer + fraction / 1000000;
    return value;
}
