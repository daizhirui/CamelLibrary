include ../Makefile.compiler

LIB_NAME=m2core
LIBFILE_NAME=$(LIB_NAME:%=lib%.a)

all: entry.o $(LIBFILE_NAME)

# entry.o: entry.s
# 	$(AS_MIPS) $(AS_FLAGS) -o $@ $<

m2core: interrupt.o isr.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^;\
	rm $^

.PHYONE:install
install:
	mv lib$(LIB_NAME).a $(PROJECT_PATH)/release/lib
	mv entry.o $(PROJECT_PATH)/release/lib

.PHYONE:clean
clean:
	rm *.o;\
	rm *.a

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ../mcu -I ./ $< -o $@

%.o : %.s
	$(AS_MIPS) $(AS_FLAGS) -o $@ $<

lib%.a : interrupt.o isr.o
	$(AR_MIPS) $(AR_FLAGS) $@ $^;\
	rm $^
