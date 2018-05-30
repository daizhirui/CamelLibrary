include ../Makefile.compiler

LIB_NAME=math stdio stdio_fp stdlib stdlib_fp
LIB_HEADER=$(LIB_NAME:%=%.h)
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: $(LIBFILE_NAME)

libstdio.a: stdio.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^
	rm $^

libstdlib.a: stdlib.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^
	rm $^

libstdio_fp.a: stdio_fp.c
	$(GCC_MIPS) $(GCC_FLAGS) -G0 -msoft-float -I ../mcu -I ./ -o stdio_fp.o stdio_fp.c;\
	$(AR_MIPS) $(AR_FLAGS) $@ stdio_fp.o;\
	rm *.o

libstdlib_fp.a: stdlib.c stdlib_fp.c
	$(GCC_MIPS) $(GCC_FLAGS) -G0 -msoft-float -I ../mcu -I ./ -o stdlib.o stdlib.c;\
	$(GCC_MIPS) $(GCC_FLAGS) -G0 -msoft-float -I ../mcu -I ./ -o stdlib_fp.o stdlib_fp.c;\
	$(AR_MIPS) $(AR_FLAGS) $@ stdlib.o stdlib_fp.o;\
	rm *.o

libmath.a: math.c
	$(GCC_MIPS) $(GCC_FLAGS) -G0 -msoft-float -I ../mcu -I ./ -o math.o math.c;\
	$(AR_MIPS) $(AR_FLAGS) $@ math.o;\
	rm *.o

.PHYONE: install
install:
	mv $(LIBFILE_NAME) $(RELEASE_PATH)/lib
	cp $(LIB_HEADER) stdarg.h stddef.h $(RELEASE_PATH)/include

.PHYONE: clean
clean:
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu -I ./ $< -o $@
