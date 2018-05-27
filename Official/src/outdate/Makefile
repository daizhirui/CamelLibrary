include ../Makefile.compiler

LIB_NAME=csc

all: lib$(LIB_NAME).a

.PHYONE: install
install:
	mv lib$(LIB_NAME).a $(PROJECT_PATH)/release/lib/M2

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu $< -o $@

lib%.a : %.o
	$(AR_MIPS) $(AR_FLAGS) $@ $<