# Standard Input Output Library for M2  {#stdio}

To use this library, please include `stdlib.h`. If you want to use a stdio library supporting soft float, please include `stdio_fp.h` instead of `stdio.h`.

## Interface

```C
void putchar(char c);

void puts(const char* string);

char getchar();

long getnum();

unsigned long getHexNum();

char* itoa(int value, unsigned int base);

void printf(const char *format, ...);

void sprintf(char* buf, const char* format, ...);
```

## Example

```C
char a = 'H'; putchar(a);            // print 'H' to Uart0
char b = getchar();                  // get a char from Uart, then assign to b
```
