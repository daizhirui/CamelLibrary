CC = gcc

all: elf_reader convert
	mkdir -p ../release;

elf_reader:
	$(CC) -O2 -std=c99 -o ../release/elf_reader ../elf_reader/elf.c ../elf_reader/main.c

convert:
	$(CC) -O2 -std=c99 -o ../release/convert ../convert/convert.c ../convert/main.c ../elf_reader/elf.c -I ../elf_reader

test:
	../release/convert -m -v ../test/Hello_O0;
	../release/convert -m -v ../test/Hello_O2
