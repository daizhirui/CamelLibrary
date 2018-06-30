include ../../src/Makefile.compiler

C_SOURCE=c_test.c
OBJECT_FILE=$(C_SOURCE:%.c=%.o)
# TARGET_NAME=printf_test
LIBRARY_FLAGS=-L ../../release/lib -L ./
RELEASE_DIR=release
ENTRY_FILE = $(LIBRARY_PATH)/entry.o
TARTGET_ADDRESS=10000000

all: c_test

c_test_mcu: c_test.o
	mkdir -p $(RELEASE_DIR);\
	$(LD_MIPS) $(LD_FLAGS) $(LIBRARY_FLAGS) -o $(RELEASE_DIR)/$@ $(ENTRY_FILE) $^ -linterrupt -lstr;\
	$(CONVERT_MY) $(CONVERTER_OPTION) $(RELEASE_DIR)/$@;\

c_test: c_test.o# interrupt.o isr.o
	mkdir -p $(RELEASE_DIR);\
	$(LD_MIPS) $(LD_FLAGS) $(LIBRARY_FLAGS) -o $(RELEASE_DIR)/$@ $(ENTRY_FILE) $^ -lm2core;\
	$(CONVERT_MY) $(CONVERTER_OPTION) $(RELEASE_DIR)/$@;\


cpp_test:cpp_test.o
	mkdir -p $(RELEASE_DIR);\
	$(LD_MIPS) $(LD_FLAGS) $(LIBRARY_FLAGS) -o $(RELEASE_DIR)/$@ $(ENTRY_FILE) $^ -lm2core -lUART0_CPP;\
	$(CONVERT_MY) $(CONVERTER_OPTION) $(RELEASE_DIR)/$@;\

s_test: Hello.o
	mkdir -p $(RELEASE_DIR);\
	$(LD_MIPS) $(LD_FLAGS) $(LIBRARY_FLAGS) -o $(RELEASE_DIR)/$@ $(ENTRY_FILE) $^ -lm2core;\
	$(CONVERT_MY) $(CONVERTER_OPTION) $(RELEASE_DIR)/$@;\
# interrupt.o:
# 	$(GXX_MIPS) $(GXX_FLAGS) -I ../../release/include -I ./ interrupt.c -o interrupt.o;\

.PHYONE:clean
clean:
	rm $(RELEASE_DIR)/*

##############################
%.o : %.c
	$(GCC_MIPS)	$(GCC_FLAGS) -fno-builtin -I ../../release/include -I ./ $^ -o $@;\

%.o : %.cpp
	$(GXX_MIPS) $(GXX_FLAGS) -I ../../release/include -I ./ $^ -o $@

%.o : %.s
	$(AS_MIPS) $(AS_FLAGS) -o $@ $<
