include ../Makefile.compiler

LIB_NAME=UART
LIB_HEADER=$(LIB_NAME:%=%.h)
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: $(LIBFILE_NAME)

.PHYONE: install
install:
	mv $(LIBFILE_NAME) $(RELEASE_PATH)/lib
	cp $(LIB_HEADER) $(RELEASE_PATH)/include

.PHYONE: clean
clean:
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu -I ./ -I ../UART0 $< -o $@

lib%.a : %.o
	$(AR_MIPS) $(AR_FLAGS) $@ $<
