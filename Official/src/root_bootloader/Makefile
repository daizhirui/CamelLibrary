include ../Makefile.compiler

C_SOURCE=root_bootloader_test.c
OBJECT_FILE=$(C_SOURCE:%.c=%.o)
TARGET_NAME=root_bootloader_test
BINARY_PATH=./release/$(TARGET_NAME).bin
LIBRARY_PATH=../../release/lib
ENTRY_FILE = $(LIBRARY_PATH)/entry.o
SERIAL_PORT=/dev/cu.Repleo-PL2303-00001014

all: $(TARGET_NAME)

$(TARGET_NAME):$(OBJECT_FILE)
	mkdir -p release;\
	$(LD_MIPS) $(LD_FLAGS) -L $(LIBRARY_PATH) -o release/$@ $(ENTRY_FILE) $^ -lm2core -lUART0;\
	$(CONVERT_MY) $(CONVERTER_OPTION) release/$@;\
	rm *.o

upload:
	python3 $(TOOLCHAINS_DIR)/../uploader.py $(SERIAL_PORT) $(BINARY_PATH)

##############################
%.o : %.c
	$(GCC_MIPS)	$(GCC_FLAGS) -I ../../release/include -I ./ $^ -o $@
