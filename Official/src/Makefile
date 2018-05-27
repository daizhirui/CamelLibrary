include Makefile.compiler

LIBRARY_NAME = AFE boot LCD mcu SPI std string time UART0 UART0_Lin UART1 UART1_Lin 
TARGET_NAME = $(LIBRARY_NAME:%=lib%.a)
#libAFE.a libCORE.a libLCD.a libtime.a libUART0.a libUART1.a libUARTx.a libUART0_Lin.a libUART1_Lin.a libSPI.a libstr.a libstring.a libextend_str.a libprobe.a

all: $(TARGET_NAME)

############### String Library ################
lib%.a:%
	cd $<;\
	make;\
	make install;\
	cd ..

build_test: build_test.c
	cp $(RELEASE_PATH)/include/* $(TOOLCHAINS_DIR)/../include;\
	cp $(RELEASE_PATH)/lib/* $(TOOLCHAINS_DIR)/../lib;\
	mkdir -p build;\
	cd build;\
	export C_INCLUDE_PATH=$(C_INCLUDE_PATH);\
	export LIBRARY_PATH=$(LIBRARY_PATH);\
	$(GCC_MIPS) $(GCC_FLAGS) -o $@.o -I $(C_INCLUDE_PATH) ../$<
	$(LD_MIPS) $(LD_FLAGS) -L $(LIBRARY_PATH) -o build/$@ $(LIBRARY_PATH)/entry.o build/$@.o -lm2core -lstdio
	$(CONVERT_MY) $(CONVERTER_OPTION) build/$@
# $(LD_MIPS) -L $(LIBRARY_PATH) --verbose | grep SEARCH_DIR | tr -s ' ;' \\012
# echo | $(GCC_MIPS) -E -Wp,-v -;


.PHYONE: install
install:
	cp ./*.h $(RELEASE_PATH)/include

.PHONY:clean
clean:
	rm $(RELEASE_PATH)/lib/*;\
	rm $(RELEASE_PATH)/include/*
