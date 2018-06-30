include ../Makefile.compiler

LIB_NAME=soft_fp
LIB_HEADER=$(LIB_NAME:%=%.h)
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: $(LIBFILE_NAME)

libsoft_fp.a: soft_fp.c
	$(GCC_MIPS) $(GCC_FLAGS) -fno-builtin -G0 -msoft-float -I ../mcu -I ./ -o soft_fp.o soft_fp.c;\
	$(AR_MIPS) $(AR_FLAGS) $@ soft_fp.o;\
	rm *.o

.PHYONE: install
install:
	mv $(LIBFILE_NAME) $(RELEASE_PATH)/lib
	cp $(LIB_HEADER) $(RELEASE_PATH)/include

.PHYONE: clean
clean:
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -fno-builtin -I ../mcu -I ./ $< -o $@
