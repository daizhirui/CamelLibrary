include ../Makefile.compiler

LIB_NAME=m2core
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: entry.o $(LIBFILE_NAME)
	$(AS_MIPS) $(AS_FLAGS) -o $(RELEASE_PATH)/lib/$@ entry.s

libm2core.a: interrupt.o isr.o
	$(AR_MIPS) $(AR_FLAGS) $(RELEASE_PATH)/lib/$@ $^;\
	rm interrupt.o isr.o

.PHYONE:clean
clean:
	rm $(RELEASE_PATH)/lib/entry.o;\
	rm $(RELEASE_PATH)/lib/libm2core.a;\

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../library $< -o $@

%.o : %.s
	$(AS_MIPS) $(AS_FLAGS) -o $@ $<
