//
//  convert.h
//  convert
//
//  Created by Zhirui Dai on 2018/8/2.
//  Copyright © 2018 Zhirui Dai. All rights reserved.
//

#ifndef convert_h
#define convert_h

#include <stdio.h>
#include "elf.h"

typedef struct {
    char*       elf_fileName;
    uint8_t*    code_buf;
    uint32_t    code_buf_size;
    uint32_t    code_section_addr;
    uint8_t*    rodata_buf;
    uint32_t    rodata_buf_size;
    uint32_t    rodata_section_addr;
    uint8_t*    data_buf;
    uint32_t    data_buf_size;
    uint32_t    data_memory_addr;
    uint32_t    data_flash_begin_addr;
    uint32_t    data_flash_end_addr;
    uint32_t    bss_begin_addr;
    uint32_t    bss_end_addr;
    uint32_t    bss_size;
    uint32_t    global_pointer_addr;
    uint32_t    stack_pointer_addr;
} M2_BIN_T;

typedef struct {
    uint32_t code_0x0;
    uint32_t code_0x4;
    uint32_t code_0x8;
    uint32_t code_0xc;
    uint32_t code_0x10;
    uint32_t code_0x14;
    uint32_t code_0x18;
} USERBOOTLOADER_T;

#define FLASH_ADDR_THRESHOLD    0x1000001c

#define INSTR_CODE_SECTION      ".text"
#define RODATA_SECTION          ".rodata"
#define DATA_SECTION            ".data"
#define BSS_SECTION             ".bss"

#define M2_STACK_POINTER_ADDR   0x01001f00
#define M2_DEFAULT_DATA_ADDR    0x01000010
#define M2_DEFAULT_TARGET_ADDR  0x10000000

extern uint8_t convert_debug;
extern uint32_t targetAddress;
extern uint32_t dataAddress;

M2_BIN_T M2_Convert_toBin(ELF_T elf);
void M2_Convert_freeBin(M2_BIN_T bin);
void M2_Convert_updateInstrCode(M2_BIN_T bin);
void M2_Convert_writeBinToDisk(M2_BIN_T bin);

#endif /* convert_h */
