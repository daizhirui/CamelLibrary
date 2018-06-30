include ../Makefile.compiler

LIB_NAME=UART0
LIB_HEADER=$(LIB_NAME:%=%.h)
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: $(LIBFILE_NAME)

# UART0_CPP: UART0_CPP.cpp
# 	$(GXX_MIPS) $(GXX_FLAGS) -I ../mcu -I ./ UART0_CPP.cpp -o UART0_CPP.o
# 	$(AR_MIPS) $(AR_FLAGS) libUART0_CPP.a UART0_CPP.o

.PHYONE: install
install:
	mv $(LIBFILE_NAME) $(RELEASE_PATH)/lib
	cp $(LIB_HEADER) $(RELEASE_PATH)/include

.PHYONE: clean
clean:
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu -I ./ $< -o $@

lib%.a : %.o
	$(AR_MIPS) $(AR_FLAGS) $@ $<
