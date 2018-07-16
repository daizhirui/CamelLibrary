include ../Makefile.compiler

LIBRARY_NAME = DES LCD soft_fp stdio stdio_fp stdlib stdlib_fp string time SPI 
TARGET_NAME = $(LIBRARY_NAME:%=lib%.a)
TARGET_PATH = $(LIBRARY_NAME:%=$(RELEASE_PATH)/lib/lib%.a)
HEADER_NAME = $(LIBRARY_NAME:%=%.h)
OTHER_LIBRARY_NAME = Flash Interrupt IO TC0 TC1 TC2 TC4 WDT analogIO UART mcu
OTHER_HEADER_NAME = $(OTHER_LIBRARY_NAME:%=%.h)

all: $(TARGET_NAME)
	mkdir -p $(RELEASE_PATH)/include;\
	mkdir -p $(RELEASE_PATH)/lib;\
	cp $(HEADER_NAME) $(OTHER_HEADER_NAME) $(RELEASE_PATH)/include;\


doc:
	cd ../../Documentation/Doxygen;\
	doxygen Doxyfile;\
	cd ../../src/library



.PHONY:clean
clean:
	rm $(TARGET_PATH)

##############################
%.o : %.c
	$(GCC_MIPS) $(GCC_FLAGS) -I ./ $< -o $@

lib%.a : %.o
	$(AR_MIPS) $(AR_FLAGS) $(RELEASE_PATH)/lib/$@ $<
