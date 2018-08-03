//
//  main.c
//  convert
//
//  Created by Zhirui Dai on 2018/8/2.
//  Copyright © 2018 Zhirui Dai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "elf.h"
#include "convert.h"

typedef struct {
    bool  convert;
    bool  debug;
    char* fileName;
} param_t;

static inline void printUsage() {
    printf("usage: convert <option> <elf_file>\n");
    printf("       -d specify data address in hex\n");
    printf("       -m convert the elf_file to binary\n");
    printf("       -v output debuging information\n");
    printf("       -h print this usage\n");
    printf("example:\n");
    printf("    convert -m elf_file       convert the elf file to binary file\n");
    printf("    convert -m -d elf_file    convert the elf file to binary file and\n");
    printf("                              output debugging information simultaneously\n");
    printf("    convert -d elf_file       only output the debugging information\n");
}

static inline param_t processArgs(int argc, char * argv[]) {
    param_t param;
    param.convert = false;
    param.debug = false;
    param.fileName = NULL;
    
    char option;
    while ((option = getopt(argc, argv, ":d:mvh")) != -1) {
        switch (option) {
            case 'd':
                dataAddress = (uint32_t)strtol(optarg, NULL, 16);
                break;
            case 'm':
                param.convert = true;
                break;
            case 'v':
                param.debug = true;
                break;
            case 'h':
                printUsage();
                exit(EXIT_SUCCESS);
            case '?':
                fprintf(stderr, "Unsupported option '%c'\n", optopt);
                printUsage();
                exit(EXIT_FAILURE);
            case ':':
                fprintf(stderr, "option '%c' requires a parameter\n", optopt);
                printUsage();
                exit(EXIT_FAILURE);
            default:
                fprintf(stderr, "Unknown error in processArgs\n");
                printUsage();
                exit(EXIT_FAILURE);
        }
    }
    param.fileName = argv[argc-1];
    return param;
}

int main(int argc, char * argv[]) {
    
    param_t param = processArgs(argc, argv);
    M2_BIN_T bin;
    
    if (param.debug) {
        convert_debug = 1;
    } else {
        convert_debug = 0;
    }
    
    if (param.debug || param.convert) {
        ELF_T elf = Elf_Reader_loadElf(param.fileName);
        bin = M2_Convert_toBin(elf);
        M2_Convert_updateInstrCode(bin);
    } else {
        return 0;
    }
    
    if (param.convert) {
        M2_Convert_writeBinToDisk(bin);
    }
    
    M2_Convert_freeBin(bin);
    
    return 0;
}
