//
//  main.c
//  elf_reader
//
//  Created by Zhirui Dai on 2018/7/16.
//  Copyright © 2018 Zhirui Dai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "elf.h"

static inline void printUsage() {
    printf("usage: elf_reader <elf_file path>\n");
}

int main(int argc, char * argv[]) {
    
    ELF_T elf;
    
    if (argc != 2) {
        printUsage();
        exit(EXIT_FAILURE);
    } else {
        elf = Elf_Reader_loadElf(argv[1]);
    }
    
    Elf_Reader_printFileSize(elf);
    Elf_Reader_printFileHeader(elf.fileHeader);
    Elf_Reader_printAllSectionHeaders(elf);
    Elf_Reader_printAllProgramHeaders(elf);
    if (elf.regInfo != NULL) {
        Elf_Reader_printMIPSRegInfo(elf.regInfo);
    }
    
    return 0;
}
