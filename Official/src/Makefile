# Compiler definition
GCC_MIPS = ../../ToolChains/bin/mips-netbsd-elf-gcc
GCC_OPTION = -EL -DPRT_UART -march=MIPS1 -c
AS_MIPS =  ../../ToolChains/bin/mips-netbsd-elf-as
AS_OPTION = -EL
LD_MIPS =  ../../ToolChains/bin/mips-netbsd-elf-ld
LD_OPTION = -EL -eentry -s -N -Ttext $(TARTGET_ADDRESS) -Tdata $(DATA_ADDRESS) --section-start .rodata=$(RODATA_ADDRESS)
OBJDUMP_MIPS =  ../../ToolChains/bin/mips-netbsd-elf-objdump
AR_MIPS =  ../../ToolChains/bin/mips-netbsd-elf-ar
AR_OPTION = rcs
CONVERT_MY = ./convert
LIB_DIR = ../lib/M2

all:libAFE.a libCORE.a libLCD.a libtime.a libUART0.a libUART1.a libUARTx.a libUART0_Lin.a libUART1_Lin.a libSPI.a libstr.a libstring.a libextend_str.a libprobe.a libmath.a
	cp boot/*.a $(LIB_DIR)
	cp boot/*.o $(LIB_DIR)

# Static library:
libAFE.a:AFE.c AFE.h
	$(GCC_MIPS) $(GCC_OPTION) AFE.c -o $(LIB_DIR)/AFE.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libAFE.a $(LIB_DIR)/AFE.o
libCORE.a:CORE.c CORE.h
	$(GCC_MIPS) $(GCC_OPTION) CORE.c -o $(LIB_DIR)/CORE.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libCORE.a $(LIB_DIR)/CORE.o
libLCD.a:LCD.c LCD.h
	$(GCC_MIPS) $(GCC_OPTION) LCD.c -o $(LIB_DIR)/LCD.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libLCD.a $(LIB_DIR)/LCD.o
libtime.a:time.c time.h
	$(GCC_MIPS) $(GCC_OPTION) time.c -o $(LIB_DIR)/time.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libtime.a $(LIB_DIR)/time.o
libUART0.a:UART0.c UART0.h
	$(GCC_MIPS) $(GCC_OPTION) UART0.c -o $(LIB_DIR)/UART0.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libUART0.a $(LIB_DIR)/UART0.o
libUART0_Lin.a:UART0_Lin.c UART0_Lin.h
	$(GCC_MIPS) $(GCC_OPTION) UART0_Lin.c -o $(LIB_DIR)/UART0_Lin.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libUART0_Lin.a $(LIB_DIR)/UART0_Lin.o
libUART1.a:UART1.c UART1.h
	$(GCC_MIPS) $(GCC_OPTION) UART1.c -o $(LIB_DIR)/UART1.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libUART1.a $(LIB_DIR)/UART1.o
libUARTx.a:UARTx.c UARTx.h
	$(GCC_MIPS) $(GCC_OPTION) UARTx.c -o $(LIB_DIR)/UARTx.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libUARTx.a $(LIB_DIR)/UARTx.o
libUART1_Lin.a:UART1_Lin.c UART1_Lin.h
	$(GCC_MIPS) $(GCC_OPTION) UART1_Lin.c -o $(LIB_DIR)/UART1_Lin.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libUART1_Lin.a $(LIB_DIR)/UART1_Lin.o
libSPI.a:SPI.c SPI.h
	$(GCC_MIPS) $(GCC_OPTION) SPI.c -o $(LIB_DIR)/SPI.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libSPI.a $(LIB_DIR)/SPI.o
libstr.a:
	$(GCC_MIPS) $(GCC_OPTION) str.c -o $(LIB_DIR)/str.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libstr.a $(LIB_DIR)/str.o
libstring.a:string.c string.h
	$(GCC_MIPS) $(GCC_OPTION) string.c -o $(LIB_DIR)/string.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libstring.a $(LIB_DIR)/string.o
libextend_str.a:extend_str.c extend_str.h
	$(GCC_MIPS) $(GCC_OPTION) extend_str.c -o $(LIB_DIR)/extend_str.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libextend_str.a $(LIB_DIR)/extend_str.o
libprobe.a:probe.c probe.h
	$(GCC_MIPS) $(GCC_OPTION) probe.c -o $(LIB_DIR)/probe.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libprobe.a $(LIB_DIR)/probe.o

libmath.a: math.c math.h
	$(GCC_MIPS) $(GCC_OPTION) -G0 -msoft-float math.c -o $(LIB_DIR)/math.o
	$(AR_MIPS) $(AR_OPTION) $(LIB_DIR)/libmath.a $(LIB_DIR)/math.o

.PHONY:clean
clean:
	rm $(LIB_DIR)/*.o $(LIB_DIR)/*.a