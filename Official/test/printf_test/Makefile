include ../../src/Makefile.compiler

C_SOURCE=printf_test.c
OBJECT_FILE=$(C_SOURCE:%.c=%.o)
TARGET_NAME=printf_test
LIBRARY_PATH=../../release/lib
ENTRY_FILE = $(LIBRARY_PATH)/entry.o
TARTGET_ADDRESS=10001f00

all: $(TARGET_NAME)

$(TARGET_NAME):$(OBJECT_FILE)
	mkdir -p release;\
	$(LD_MIPS) $(LD_FLAGS) -L $(LIBRARY_PATH) -o release/$@ $(ENTRY_FILE) $^ -lm2core -lstdio;\
	$(CONVERT_MY) $(CONVERTER_OPTION) release/$@;\
	rm *.o

##############################
%.o : %.c
	$(GCC_MIPS)	$(GCC_FLAGS) -I ../../release/include -I ./ $^ -o $@
