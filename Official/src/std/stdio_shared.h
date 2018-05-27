/**
 * @brief 
 * 
 * @file stdio_shared.h
 * @author your name
 * @date 2018-05-27
 */

#ifndef __M2_STDIO_SHARED_H__
#define __M2_STDIO_SHARED_H__

// for itoa, ftoa, printf
static char buf[256];
char * _strcat(char *dest, const char * src);
unsigned int _strlen(const char * str);

#endif