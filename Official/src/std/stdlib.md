# Standard Library for M2  {#stdlib}

To use this library, please include `stdlib.h`. If you want to use a stdlib library supporting soft float, please include `stdlib_fp.h` instead of `stdlib.h`.

## Interface

```C
long atoi(const char* str);

unsigned long xtoi(const char* str);
```

## Example

```C
long i = atoi("1234");            // convert string decimal "1234" to number
long j = xtoi("1f80");            // convert string hex "1f80" to number
```
