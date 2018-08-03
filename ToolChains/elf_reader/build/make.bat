cd /D "%~dp0"
set path=%path%;C:\MinGW\bin
"C:\MinGW\bin\mingw32-gcc.exe" -O2 -std=c99 -o ..\release\elf_reader.exe ..\elf_reader\elf.c ..\elf_reader\main.c
"C:\MinGW\bin\mingw32-gcc.exe" -O2 -std=c99 -o ..\release\convert.exe ..\convert\convert.c ..\convert\main.c ..\elf_reader\elf.c -I ..\elf_reader
