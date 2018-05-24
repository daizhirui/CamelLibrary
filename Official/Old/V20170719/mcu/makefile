# Compiler definition
GCC_MIPS = mips-netbsd-elf-gcc
GCC_OPTION = -EL -DPRT_UART -march=MIPS1 -c
AS_MIPS = mips-netbsd-elf-as
AS_OPTION = -EL
LD_MIPS = mips-netbsd-elf-ld
LD_OPTION = -EL -eentry -s -N -Ttext $(TARTGET_ADDRESS) -Tdata $(DATA_ADDRESS) --section-start .rodata=$(RODATA_ADDRESS)
OBJDUMP_MIPS = mips-netbsd-elf-objdump
AR_MIPS = mips-netbsd-elf-ar
AR_OPTION = rcs
CONVERT_MY = /opt/cross/gcc-mips/convert

all:libAFE.a libCORE.a libLCD.a libRTC.a libUART.a libUART1.a
#libFLASH.a not completed yet

# Static library
libAFE.a:AFE.o
	$(AR_MIPS) $(AR_OPTION) lib/libAFE.a lib/AFE.o
libCORE.a:CORE.o
	$(AR_MIPS) $(AR_OPTION) lib/libCORE.a lib/CORE.o
libLCD.a:LCD.o
	$(AR_MIPS) $(AR_OPTION) lib/libLCD.a lib/LCD.o
libRTC.a:RTC.o
	$(AR_MIPS) $(AR_OPTION) lib/libRTC.a lib/RTC.o
libUART.a:UART.o
	$(AR_MIPS) $(AR_OPTION) lib/libUART.a lib/UART.o
libUART1.a:UART1.o
	$(AR_MIPS) $(AR_OPTION) lib/libUART1.a lib/UART1.o

#libFLASH.a:FLASH.o
#	$(AR_MIPS) $(AR_OPTION) lib/libFLASH.a lib/FLASH.o

# Objects
AFE.o:AFE.c
	$(GCC_MIPS) $(GCC_OPTION) AFE.c -o lib/AFE.o
CORE.o:CORE.c
	$(GCC_MIPS) $(GCC_OPTION) CORE.c -o lib/CORE.o
LCD.o:LCD.c
	$(GCC_MIPS) $(GCC_OPTION) LCD.c -o lib/LCD.o
RTC.o:RTC.c
	$(GCC_MIPS) $(GCC_OPTION) RTC.c -o lib/RTC.o
UART.o:UART.c
	$(GCC_MIPS) $(GCC_OPTION) UART.c -o lib/UART.o
UART1.o:UART1.c
	$(GCC_MIPS) $(GCC_OPTION) UART1.c -o lib/UART1.o

#FLASH.o:FLASH.c
#	$(GCC_MIPS) $(GCC_OPTION) FLASH.c -o lib/FLASH.o

.PHONY:clean
clean:
	rm lib/*.o lib/*.a
