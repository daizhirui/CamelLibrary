# Camel_Library
Official Library for Camel Micro products. This library is embedded in [CamelStudioX](https://github.com/daizhirui/CamelStudioX_Mac/releases/latest).
----

## Documentation

[Camel Library Documentation](https://daizhirui.github.io/Camel_Library/)

## History

### 13.07.2018

- Fix a bug of RT_SYSINT_GetFlag
- use more inline functions
- recompile with -O2 -msoft-float
- Improve soft_fp by using union to convert between float and uint32 or double and uint32[2]
- Update documentation

### 11.07.2018

- Improve ```void RT_TCx_TimerSet1us(uint32_t T, switch_t irqEn)```, transform them to inline functions and use a better algorithm to determine the ```clk``` and ```ref```.

### 06.07.2018

- Merge code in interrupt.c to isr.s to increase the speed of entering the interrupt state.
- Remove m2core, whose name is quite vague.
- Add isr(Interrupt Service Routine) library.
- Convert some functions from macro to inline functions to make them safer.
- Rename ```RT_Clr_Sram``` to ```RT_Sram_Clear``` and ```RT_Sram_Clear``` now can clear 7k-byte sram space instead of 2k bytes.

### 04.07.2018

- Reorganize the source files.
- Update the theme of the documentation site.
- Change the repository name from `CamelStudio_Library` to `Camel_Library`

### 24.06.2018

- Add documentation about TC0,1,2,4, Flash, Interrupt.

### 23.06.2018

- Add documentation about SPI.

### 22.06.2018

- Add documentation about UART.
- Use a new doxygen theme.

### 16.06.2018

- Remove some unused libraries. Basic library will focus more on standard requirement.

### 15.06.2018

- Add Data Encryption Standard (DES) Library.

### 13.06.2018

- Add .data loader to boot loader and update convert to make it compatible.
- Fix a bug of .bss section location in convert.
