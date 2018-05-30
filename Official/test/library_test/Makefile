include ../../src/Makefile.compiler

C_SOURCE=library_test.c
OBJECT_FILE=$(C_SOURCE:%.c=%.o)
TARGET_NAME=library_test
LIBRARY_PATH=../../release/lib
ENTRY_FILE = $(LIBRARY_PATH)/entry.o
TARTGET_ADDRESS=10000000

all: $(TARGET_NAME)

$(TARGET_NAME):$(OBJECT_FILE)
	mkdir -p release;\
	cd ../../;\
	make;\
	cd test/library_test;\
	$(LD_MIPS) $(LD_FLAGS) -L $(LIBRARY_PATH) -o release/$@ $(ENTRY_FILE) $^ -lm2core -lstdio;\
	$(CONVERT_MY) $(CONVERTER_OPTION) release/$@

##############################
%.o : %.c
	$(GCC_MIPS)	$(GCC_FLAGS) -I ../../release/include -I ./ $^ -o $@
