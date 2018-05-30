include ../Makefile.compiler

LIB_NAME=m2core m2core_autoUart
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: entry.o $(LIBFILE_NAME)

# entry.o: entry.s
# 	$(AS_MIPS) $(AS_FLAGS) -o $@ $<

libm2core.a: interrupt.o isr.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^;\

libm2core_autoUart.a: autoUart.o isr.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^;\

.PHYONE:install
install:
	cp autoUart.h $(PROJECT_PATH)/release/include
	mv $(LIBFILE_NAME) $(PROJECT_PATH)/release/lib
	mv entry.o $(PROJECT_PATH)/release/lib

.PHYONE:clean
clean:
	rm *.o;\
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu -I ../UART0 -I ../std -I ./ $< -o $@

%.o : %.s
	$(AS_MIPS) $(AS_FLAGS) -o $@ $<
