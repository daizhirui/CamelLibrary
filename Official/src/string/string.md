# String Library for M2  {#string}

To use this library, please include `string.h`.

## Interface

```C
void *memchr(const void *str, int c, size_t n);

void memcmp(const void *str, int c, size_t n);

void * memcpy(void * dest, const void * src, size_t n);

void * memmove(void * dest, const void * src, size_t n);

void * memset(void *str, int c, size_t n);

char * strcat(char *dest, const char * src);

char * strncat(char *dest, const char * src, size_t n);

char * strchr(const char *str, int c);

int strcmp(const char * s1, const char * s2);

int strncmp(const char * s1, const char * s2, size_t n);

char * strcpy(char * dest, const char * src);

char * strncpy(char * dest, const char * src, size_t n);

size_t strlen(const char * str);

char * strstr(const char *s1, const char * s2);
```

## Example

```C
#include "stdio.h"

void Example_strlen() {
    printf("%s has %d chars", s, strlen(s));  // strlen
}

void Example_strncmp() {
    int ptr;
    ptr=strncmp(buf2, buf1, 3); // string comparison
}
```
