# CamelStudio_Library
Official Library for Camel Micro products. This library is embedded in [CamelStudioX](https://github.com/daizhirui/CamelStudioX_Mac/releases/latest).
----

## Library List
- entry.o
- ~~gdbentry.o~~
- libAFE.a
- libLCD.a
- libSPI.a
- libUART0.a
- libUART0_Lin.a
- libUART1.a
- libUART1_Lin.a
- ~~libgdb.a~~
- ~~libinterrupt.a~~
- libmath.a
- ~~libmsgdb.a~~
- ~~libmsinterrupt.a~~
- ~~libprobe.a~~
- ~~libstr.a~~
- libstring.a
- libtime.a

**New**

- libstdio.a
- libstdio_fp.a
- libstdlib.a
- libstdlib_fp.a
- libm2core.a
- libsoft_fp.a

## Documentation

- [DES Library](Official/src/DES/README.md)

## History

### 15.06.2018

- Add Data Encryption Standard (DES) Library.

### 13.06.2018

- Add .data loader to boot loader and update convert to make it compatible.
- Fix a bug of .bss section location in convert.
