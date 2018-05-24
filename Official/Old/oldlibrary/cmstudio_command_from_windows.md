####### C build library
"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-gcc.exe" -EL -DPRT_UART -march=MIPS1 -c -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/M2 -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/std -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/core -o lib/hello.o hello.c

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-ar.exe" rcs lib/libhello.a lib/hello.o

###### A build library
"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-as.exe" -EL -o lib/hello.o hello.s

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-gcc.exe" -EL -DPRT_UART -march=MIPS1 -c -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/M2 -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/std -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/core -o lib/interrupt.o interrupt.c

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-ar.exe" rcs lib/libhello.a lib/hello.o lib/interrupt.o

###### C build binary
"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-gcc.exe" -EL -DPRT_UART -march=MIPS1 -c -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/M2 -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/std -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/core -o release/hello.o hello.c

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-ld.exe" -EL -eentry -s -N -Ttext 10000000 -o release/hello C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/M2/entry.o release/hello.o -L C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/std -l string -L C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/M2 -l interrupt -l str

"C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/convert.exe" -m release/hello

###### A build binary
"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-as.exe" -EL -o release/hello.o hello.s

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-gcc.exe" -EL -DPRT_UART -march=MIPS1 -c -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/M2 -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/std -I C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/include/core -o release/interrupt.o interrupt.c

"C:\CamelStudio\mips-mti-elf\bin/mips-mti-elf-ld.exe" -EL -eentry -s -N -Ttext 10000000 -Tdata 01000010 --section-start .rodata=10003300 -o release/hello C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/M2/entry.o release/hello.o release/interrupt.o -L C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/std -l string -L C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/lib/M2 -l interrupt -l str

"C:/CamelStudio/CamelStudioRelease5-15-2017/CamelStudio/convert.exe" -m release/hello