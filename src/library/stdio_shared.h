/**
 * @brief
 *
 * @file stdio_shared.h
 * @author your name
 * @date 2018-05-27
 */

#ifndef __M2_STDIO_SHARED_H__
#define __M2_STDIO_SHARED_H__

/*! \cond PRIVATE */
// for itoa, ftoa
static char __convertBuffer[33];
static char __printfBuffer[128];
char* _xtoa(unsigned long num);
char * _strcat(char *dest, const char * src);
unsigned int _strlen(const char * str);
/*! \endcond */

#endif
