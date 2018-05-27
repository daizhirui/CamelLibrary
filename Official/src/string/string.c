/*--------------------------------------------------------------------
 * TITLE: M2 Hardware Definition
 * AUTHOR: John & Jack 
 * DATE CREATED: 2017/11/1
 * FILENAME: string.c
 * PROJECT: M2Library
 * COPYRIGHT: Camel Microelectronics, Ltd.
 * DESCRIPTION:
 * NOTE:
 *      This library has been checked. --Astro, 2017/11/3
 *--------------------------------------------------------------------*/
#include "string.h"
void *memchr(const void *str, int c, size_t n)
{
    unsigned char *p = (unsigned char*)str;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}
int memcmp(const void * str1, const void * str2, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)str1, *p2 = (const unsigned char *)str2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}
void * memcpy(void * dest, const void * src, size_t n)
{
    register unsigned char* p=(unsigned char *)dest;
    register unsigned const char* q=(const unsigned char *)src;
    while(n--)
        *p++ = (unsigned char)*q++;
    return dest;
}
void * memmove(void * dest, const void * src, size_t n)
{
    register unsigned char *pd = (unsigned char *)dest;
    register const unsigned char *ps = (const unsigned char *)src;
    if (ps < pd)
        for (pd += n, ps += n; n--;)
            *--pd = *--ps;
    else
        while(n--)
            *pd++ = *ps++;
    return dest;
}
void * memset(void *str, int c, size_t n)
{
    register unsigned char* p=(unsigned char *)str;
    while(n--)
        *p++ = (unsigned char)c;
    return str;
}
char * strcat(char *dest, const char * src)
{
    char *ret = dest;
    while (*dest)
        dest++;
    while (*dest++ = *src++)
        ;
    return ret;
}
char * strncat(char *dest, const char * src, size_t n)
{
    char *ret = dest;
    while (*dest)
        dest++;
    while (n--)
        if (!(*dest++ = *src++))
            return ret;
    *dest = 0;
    return ret;
}
char * strchr(const char *str, int c)
{
	while (*str != (char)c)
        if (!*str++)
            return 0;
    return (char *)str;
}
int strcmp(const char * s1, const char * s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}
int strncmp(const char * s1, const char * s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}
char * strcpy(char * dest, const char * src)
{
    char *ret = dest;
    while (*dest++ = *src++)
        ;
    return ret;
}
char * strncpy(char * dest, const char * src, size_t n)
{
    char *ret = dest;
    do {
        if (!n--)
            return ret;
    } while (*dest++ = *src++);
    while (n--)
        *dest++ = 0;
    return ret;
}
size_t strlen(const char * str)
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
char * strstr(const char *s1, const char * s2)
{
    size_t n = strlen(s2);
    char * p = (char *)s1;
    while(*p)
        if(!memcmp((const char *)p++,s2,n))
            return p-1;
    return 0;
}
