include ../Makefile.compiler

LIB_NAME=mcu
LIB_HEADER=$(LIB_NAME:%=%.h)
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: $(LIBFILE_NAME)

.PHYONE: install
install:
	mv $(LIBFILE_NAME) $(RELEASE_PATH)/lib
	cp $(LIB_HEADER) $(RELEASE_PATH)/include

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) $< -o $@

lib%.a : %.o
	$(AR_MIPS) $(AR_FLAGS) $@ $<