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

# Library path definition
LIBRARY = ../M2-mcu/lib

all:libgdb.a libinterrupt.a libmsgdb.a libmsinterrupt.a libstr.a libstring.a

# Static library
GDB_OBJECT = isr.o entry.o gdb.o gdbinterrupt.o probe.o io.o
libgdb.a:$(GDB_OBJECT)
	cd lib;$(AR_MIPS) $(AR_OPTION) libgdb.a $(GDB_OBJECT);cd ..
INTERRUPT_OBJECT = entry.o isr.o interrupt.o io.o ##COMM.o
## COMM.o seems lost
libinterrupt.a:$(INTERRUPT_OBJECT)
	cd lib;$(AR_MIPS) $(AR_OPTION) libinterrupt.a $(INTERRUPT_OBJECT);cd ..
MSGDB_OBJECT = msgdb.o isr.o probe.o io.o
libmsgdb.a:$(MSGDB_OBJECT)
	cd lib;$(AR_MIPS) $(AR_OPTION) libmsgdb.a $(MSGDB_OBJECT);cd ..
MSINTERRUPT_OBJECT = entry.o isr.o msinterrupt.o io.o
libmsinterrupt.a:$(MSINTERRUPT_OBJECT)
	cd lib;$(AR_MIPS) $(AR_OPTION) libmsinterrupt.a $(MSINTERRUPT_OBJECT);cd ..
libstr.a:str.o
	cd lib;$(AR_MIPS) $(AR_OPTION) libstr.a str.o;cd ..
libstring.a:string.o
	cd lib;$(AR_MIPS) $(AR_OPTION) libstring.a string.o;cd ..

# Objects
isr.o:isr.s
	$(AS_MIPS) $(AS_OPTION) -o lib/isr.o isr.s
io.o:io.s
	$(AS_MIPS) $(AS_OPTION) -o lib/io.o io.s
entry.o:entry.s
	$(AS_MIPS) $(AS_OPTION) -EL -o lib/entry.o entry.s
probe.o:probe.c
	$(GCC_MIPS) $(GCC_OPTION) -o lib/probe.o probe.c
gdb.o:gdb.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/gdb.o gdb.c
gdbinterrupt.o:gdbinterrupt.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/gdbinterrupt.o gdbinterrupt.c
interrupt.o:interrupt.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/interrupt.o interrupt.c
msgdb.o:msgdb.c MAX3420E.h
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -l MAX3420E -o lib/msgdb.o msgdb.c 
msinterrupt.o:msinterrupt.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/msinterrupt.o msinterrupt.c
str.o:str.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/str.o str.c
string.o:string.c
	$(GCC_MIPS) $(GCC_OPTION) -I $(LIBRARY) -o lib/string.o string.c

.PHONY:clean
clean:
	rm lib/*.o lib/*.a