#-----------------------------------------------------------
# This make file is for generating the whole library for M2
# base on macOS platform.
# Author: ASTRO
# Date: 2017-07-17
#-----------------------------------------------------------
M2_MCU = AFE.h CORE.h EXTIN.h FLASH.h LCD.h mcu.h MCUIO.h RTC.h SPI.h TC0.h TC1.h TC2.h TC4.h UART.h WDT.h
M2_GDB = MAX3420E.h probe_def.h probe.h stddef.h str.h string.h 
all:
	mkdir -p include include/M2 include/std lib lib/M2 lib/std; \
	cd M2-mcu;make -f makefile;cp $(M2_MCU) ../include/M2; \
	cd lib;cp *.a ../../lib/M2;cd ..; \
	cd ../M2gdb;make -f makefile;cp $(M2_GDB) ../include/M2; \
	cp stddef.h string.h ../include/std; \
	cd lib;cp *.a ../../lib/M2;cp entry.o gdbentry.o ../../lib/M2;cp libstring.a ../../lib/std;cd ../../;