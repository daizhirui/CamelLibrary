//convert.c by Steve Rhoads 4/26/01
//Now uses the ELF format (get gccmips_elf.zip)
//set $gp and zero .sbss and .bss
//Reads test.axf and creates code.txt
//
// add 3 op
// now, it can take rodata (compiled at 0x01000010), resulting e_phnum > 1
// .rodata is now e_phnum = 2, p_vaddr > BUF_SIZE (1024*1024*4)
// if no address action is set in compiling & link, e_phnum = 1
//
// convert [-n, -p, -m] [inputfile]
//
//          -n: no convert
//          -p: plasma convert, start 0
//          -m: m0 convert, start 28
//
//     --> inputfile.txt inputfile.bin
//         inputfile.txt inputfile2.bin (rodata)
//
// John & Matt
//
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define BUF_SIZE (1024*1024*4)
/*Assumes running on PC little endian*/
/*
 The following should be commented for LE mips compiled code
 otherwise seg fault

 #ifndef USE_BIG_ENDIAN
 #define ntohl(A) (((A)>>24)|(((A)&0x00ff0000)>>8)|(((A)&0xff00)<<8)|((A)<<24))
 #define ntohs(A) (uint16)((((A)&0xff00)>>8)|((A)<<8))
 #else
 */
#undef ntohl
#undef ntohs
#define ntohl(A) A
#define ntohs(A) A
// #endif

#define EI_NIDENT 16
#define SHT_PROGBITS 1
#define SHT_STRTAB 3
#define SHT_NOBITS 8

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef struct
{
    uint8 e_ident[EI_NIDENT];
    uint16 e_e_type;
    uint16 e_machine;
    uint32 e_version;
    uint32 e_entry;
    uint32 e_phoff;
    uint32 e_shoff;
    uint32 e_flags;
    uint16 e_ehsize;
    uint16 e_phentsize;
    uint16 e_phnum;
    uint16 e_shentsize;
    uint16 e_shnum;
    uint16 e_shstrndx;
} ElfHeader;    // 52 bytes

typedef struct
{
    uint32 p_type;
    uint32 p_offset;
    uint32 p_vaddr;
    uint32 p_paddr;
    uint32 p_filesz;
    uint32 p_memsz;
    uint32 p_flags;
    uint32 p_align;
} Elf32_Phdr;   // 32 bytes

typedef struct
{
    uint32 sh_name;
    uint32 sh_type;
    uint32 sh_flags;
    uint32 sh_addr;
    uint32 sh_offset;
    uint32 sh_size;
    uint32 sh_link;
    uint32 sh_info;
    uint32 sh_addralign;
    uint32 sh_entsize;
} Elf32_Shdr;   // 40 bytes

typedef struct
{
    uint32 ri_gprmask;
    uint32 ri_cprmask[4];
    uint32 ri_gp_value;
} ELF_RegInfo;  // 40 bytes

#define PT_MIPS_REGINFO  0x70000000
#define SHT_MIPS_REGINFO 0x70000006

void set_low(uint8 *ptr, uint32 address, uint32 value)
{
    uint32 opcode;
    opcode = *(uint32 *)(ptr + address);
    opcode = ntohl(opcode);
    opcode = (opcode & 0xffff0000) | (value & 0xffff);
    opcode = ntohl(opcode);
    *(uint32 *)(ptr + address) = opcode;
}

int main(int argc, char *argv[])
{
    FILE *infile, *binFile, *txtFile, *rodataBin, *rodataTxt, *coefile, *dataBin, *dataTxt;
    uint8 *buf, *code, *rodataCode, *dataCode;
    long size, stack_pointer;
    uint32 d, i, gp_ptr = 0, gp_ptr_backup = 0;
    uint32 binLength = 0;
    uint32 instructionAddress = 0, instructionVirtualAddr = 0, instructionLength = 0, codeLength = 0;
    uint32 rodataAddress = 0, rodataLength=0;
    uint32 data_start_bin = 0, data_end_bin = 0, data_addr = 0, dataLength=0;
    uint32 bss_start = 0, bss_end = 0;
    char inFileName[8192];
    char binFileName[8192], rodataBinFileName[8192], dataBinFileName[8192];
    char txtFileName[8192], rodataTxtFileName[8192], dataTxtFileName[8192], coeFileName[8192];

    ElfHeader *elfHeader;
    Elf32_Phdr *elfProgram;
    ELF_RegInfo *elfRegInfo;
    Elf32_Shdr *elfSection;
    (void)argc;
    (void)argv;
    (void)stack_pointer;
    int op, adst, debug=0;

    #if DEBUG
    printf("Size of ElfHeader: %lu\n", sizeof(ElfHeader));
    printf("Size of Elf32_Phdr: %lu\n", sizeof(Elf32_Phdr));
    printf("Size of Elf32_Shdr: %lu\n", sizeof(Elf32_Shdr));
    #endif

    // Parse parameters
    if (argc <2)
    {
        printf("usage:\n");
        printf("  convert <-n, -p, -m> <input_file> \n");
        printf("           -n: no convert, debug infor printed\n");
        printf("           -p: plasma boot convert 0-28\n");
        printf("           -m: m0 boot convert 28-56\n\n");
        printf("  <input_file> -> <input_file>.txt & <input_file>.bin\n");
        return 0;
    }

    //   printf("argc == %d:\n", argc);
    //   printf("test.axf -> code.txt & test.bin\n");
    //   infile = fopen("test.axf", "rb");
    printf("%s -> <input_file>.txt & <input_file>.bin\n", argv[2]);
    if (!strcmp( argv[1], "-n"))
    {
        op = 0; adst = 0; debug = 1;
        printf ("-> no converting\n");
    }
    else if (!strcmp( argv[1], "-p"))
    {
        op = 1; adst = 0; debug = 0;
        printf ("-> plasma converting, 0\n");
    }
    else if (!strcmp( argv[1], "-m"))
    {
        op = 2; adst = 28; debug = 0;
        printf ("-> m0 converting, 28\n");
    }
    else {
        perror("none valid: -n, -p, -m\n");
        return 0;
    }

    // open elfFile and load to buf
    strcpy(inFileName, argv[2]);
    infile = fopen(argv[2], "rb");
    if(infile == NULL)
    {
        fprintf(stderr, "Can't open %s", argv[2]);
        return -2;
    }
    buf = (uint8*)malloc(BUF_SIZE);
    size = (int)fread(buf, 1, BUF_SIZE, infile);
    fclose(infile);

    // Make sure it is an elf file
    elfHeader = (ElfHeader *)buf;
    if(strncmp((char*)elfHeader->e_ident + 1, "ELF", 3))
    {
        perror("Error:  Not an ELF file!\n");
        perror("Use the gccmips_elf.zip from opencores/projects/plasma!\n");
        return -1;
    }

    // Prepare code buffers
    code = (uint8*)malloc(BUF_SIZE);
    rodataCode = (uint8*)malloc(BUF_SIZE);   // for rodata
    dataCode = (uint8*)malloc(BUF_SIZE);   // for data
    memset(code, 0, BUF_SIZE);
    memset(rodataCode, 0, BUF_SIZE);
    memset(dataCode, 0, BUF_SIZE);

    elfHeader->e_entry = ntohl(elfHeader->e_entry);
    elfHeader->e_phoff = ntohl(elfHeader->e_phoff);
    elfHeader->e_shoff = ntohl(elfHeader->e_shoff);
    elfHeader->e_flags = ntohl(elfHeader->e_flags);
    elfHeader->e_phentsize = ntohs(elfHeader->e_phentsize);
    elfHeader->e_phnum = ntohs(elfHeader->e_phnum);
    elfHeader->e_shentsize = ntohs(elfHeader->e_shentsize);
    elfHeader->e_shnum = ntohs(elfHeader->e_shnum);

    if (debug)
    {
        printf("e_entry=0x%x \n", elfHeader->e_entry);
        printf("e_phnum=0x%x \n", elfHeader->e_phnum);
        printf("e_shnum=0x%x \n", elfHeader->e_shnum);
    }

    // Process elfProgram header: get instruction code, rodata and data
    for(i = 0; i < elfHeader->e_phnum; ++i)
    {
        elfProgram = (Elf32_Phdr *)(buf + elfHeader->e_phoff +
                                    elfHeader->e_phentsize * i);

        if (debug) {
            uint32 value = elfProgram->p_type;
            uint32 converted;
            converted = ntohl(value);
            printf("ntohl: elfProgram->p_type ~ 0x%x -> 0x%x\n",\
         elfProgram->p_type, converted);
            value = elfProgram->p_vaddr;
            converted = ntohl(value);
            printf("ntohl: elfProgram->p_vaddr ~ 0x%x -> 0x%x\n",\
         elfProgram->p_vaddr, converted);
            fflush(stdout);
        }

        elfProgram->p_type = ntohl(elfProgram->p_type);
        elfProgram->p_offset = ntohl(elfProgram->p_offset);
        elfProgram->p_vaddr = ntohl(elfProgram->p_vaddr);
        elfProgram->p_filesz = ntohl(elfProgram->p_filesz);
        elfProgram->p_memsz = ntohl(elfProgram->p_memsz);
        elfProgram->p_flags = ntohl(elfProgram->p_flags);

        elfProgram->p_vaddr -= elfHeader->e_entry;

        if (debug)
        {
            printf("debug0: e_phnum=0x%x ", elfHeader->e_shnum);
            printf("e_phnum->p_vaddr=0x%x \n", elfProgram->p_vaddr);
        }
        //
        // This is MIPS_REGINFO, update global pointer
        if(elfProgram->p_type == PT_MIPS_REGINFO)
        {
            elfRegInfo = (ELF_RegInfo*)(buf + elfProgram->p_offset);
            gp_ptr = ntohl(elfRegInfo->ri_gp_value);
        }
        //
        // this is the code (instruction code + rodata)
        //
        if(elfProgram->p_vaddr < BUF_SIZE)
        {
            instructionAddress = elfProgram->p_paddr;
            codeLength = elfProgram->p_filesz;
            binLength += codeLength;
            data_start_bin = elfProgram->p_paddr + codeLength;
            instructionVirtualAddr = elfProgram->p_vaddr;
            memcpy(code + elfProgram->p_vaddr, buf + elfProgram->p_offset, codeLength);

            if (debug)
            {
                printf("debug1: [0x%x,0x%x,0x%x,0x%x,0x%x]\n", elfProgram->p_vaddr,
                       elfProgram->p_offset, elfProgram->p_filesz, elfProgram->p_memsz,
                       elfProgram->p_flags);
                printf("debug1: codeLength = %d 0x%x\n", codeLength, codeLength);
            }
        }
        //
        // this is the rodata
        // Zhirui Dai: This is impossible to be rodata. It is .MIPS.abiflags in fact!
        // I add && elfProgram->p_paddr > 0x10000000 here. If I don't add this, it is .data in fact!
        //
        if(elfProgram->p_vaddr > BUF_SIZE && elfProgram->p_paddr > 0x10000000)
        {
            // memcpy(rodataCode, buf + elfProgram->p_offset,
            //        elfProgram->p_filesz);
            // rodataLength = elfProgram->p_filesz;
            printf(".MIPS.abiflags!\n");
            if (debug)
            {
                printf("dbug5: [0x%x,0x%x,0x%x,0x%x,0x%x]\n", elfProgram->p_vaddr,
                       elfProgram->p_offset, elfProgram->p_filesz, elfProgram->p_memsz,
                       elfProgram->p_flags);
                printf("debug6: rodataLength = %d 0x%x\n", rodataLength, rodataLength);
            }
        }
        //
        // this is the data
        //
        if(elfProgram->p_vaddr > BUF_SIZE && elfProgram->p_paddr < 0x10000000 && elfProgram->p_paddr > 0x1000000)
        {
            data_addr = elfProgram->p_paddr;
            dataLength = elfProgram->p_filesz;
            memcpy(dataCode, buf + elfProgram->p_offset, dataLength);
            if (debug)
            {
                printf("program ");
                printf("dbug7: [0x%x,0x%x,0x%x,0x%x,0x%x]\n", elfProgram->p_vaddr,
                       elfProgram->p_offset, elfProgram->p_filesz, elfProgram->p_memsz,
                       elfProgram->p_flags);
                printf("debug8: rodataLength = %d 0x%x\n", rodataLength, rodataLength);
            }
        }

    }

    // append data section if it exists
    if (dataLength > 0)
    {
        memcpy(code + instructionVirtualAddr + codeLength, dataCode, dataLength);   // append data after instruction code and rodata.
        binLength += dataLength;
        // Calculate data_end_bin
        data_end_bin = data_start_bin + dataLength;
    }
    else    // No data section!!
    {
        data_start_bin = instructionAddress + binLength;
        data_end_bin = data_start_bin;
        data_addr = 0x01000010;     // set data_addr to 0x01000010, bss may need it!
    }

    // START TO PROCESS global_pointer, stack_pointer, bss_section, data_section
    for(i = 0; i < elfHeader->e_shnum; ++i)
    {
        elfSection = (Elf32_Shdr *)(buf + elfHeader->e_shoff +
                                    elfHeader->e_shentsize * i);
        elfSection->sh_name = ntohl(elfSection->sh_name);
        elfSection->sh_type = ntohl(elfSection->sh_type);
        elfSection->sh_addr = ntohl(elfSection->sh_addr);
        elfSection->sh_offset = ntohl(elfSection->sh_offset);
        elfSection->sh_size = ntohl(elfSection->sh_size);

        if(elfSection->sh_type == SHT_MIPS_REGINFO)
        {
            if (debug) {
                printf("Section header %d type: 0x%x(SHT_MIPS_REGINFO), offset: 0x%x, addr: 0x%x, file size: 0x%x\n",\
                       i,elfSection->sh_type, elfSection->sh_offset, elfSection->sh_addr, elfSection->sh_size);
            }
            elfRegInfo = (ELF_RegInfo*)(buf + elfSection->sh_offset);
            gp_ptr = ntohl(elfRegInfo->ri_gp_value);

            if (debug)
            {
                printf("SHT_MIPS_REGINFO\n");
                printf("elfSection->sh_name=0x%x  ", elfSection->sh_name);
                printf("elfSection->sh_addr=0x%x\n", elfSection->sh_addr);
                printf("gp_ptr=0x%x  ", gp_ptr);
            }
        }
        //
        // Program data ( instruction code, data, rodata )
        //
        if(elfSection->sh_type == SHT_PROGBITS)
        {
            if (debug) {
                printf("Section header %d type: 0x%x(SHT_PROGBITS), offset: 0x%x, addr: 0x%x, file size: 0x%x\n",\
                       i,elfSection->sh_type, elfSection->sh_offset, elfSection->sh_addr, elfSection->sh_size);
            }

            if(elfSection->sh_addr > gp_ptr_backup)
                gp_ptr_backup = elfSection->sh_addr;    // update global_pointer

            if (debug)
            {
                printf("SHT_PROGBITS\n");
                printf("elfSection->sh_name=0x%x  ", elfSection->sh_name);
                printf("elfSection->sh_addr=0x%x\n", elfSection->sh_addr);
                printf("gp_ptr_backup=0x%x\n", gp_ptr_backup);
            }

            if (elfSection->sh_addr == instructionAddress) {    // instruction code
                instructionLength = elfSection->sh_size;    // get the length of the instruction code
            }

            if (elfSection->sh_addr == instructionAddress + instructionLength) {    // rodata
                rodataAddress = elfSection->sh_addr;    // get the beginning address of rodata
                rodataLength = elfSection->sh_size;     // get the length of rodata section
                memcpy(rodataCode, code + instructionLength, rodataLength); // copy rodata section
            }
        }
        //
        // Program space with no data (bss)
        //
        if(elfSection->sh_type == SHT_NOBITS)
        {
            if (debug) {
                printf("Section header %d type: 0x%x(SHT_NOBITS), offset: 0x%x, addr: 0x%x, file size: 0x%x\n",\
                       i,elfSection->sh_type, elfSection->sh_offset, elfSection->sh_addr, elfSection->sh_size);
                printf("SHT_NOBITS\n");
                printf("elfSection->sh_name=0x%x  ", elfSection->sh_name);
                printf("elfSection->sh_addr=0x%x\n", elfSection->sh_addr);
            }

            if(bss_start == 0)
            {
                bss_start = elfSection->sh_addr;
            }

            bss_end = elfSection->sh_addr + elfSection->sh_size;
        }
    }

    if(codeLength > bss_start - elfHeader->e_entry)
    {
        printf("!!!!codeLength change....\n");
        printf("bss_start=0x%x  ", bss_start);
        printf("elfSection->e_entry=0x%x  \n", elfHeader->e_entry);
        // ???? this causes no data prog codeLength = 0
        //      codeLength = bss_start - elfHeader->e_entry;
    }
    //
    // No bss section is detected.
    //
    if(bss_start == 0)
    {
        //bss_start = codeLength;
        //bss_end = codeLength + 4;
        bss_start = data_addr;  // bss section is after data section in the sram!
        bss_end = bss_start;
    }
    //
    // No information about gp_ptr is found before.
    if(gp_ptr == 0)
        gp_ptr = gp_ptr_backup + 0x7ff0;

    //------------------------------------------------------------
    // be carefull for 3 ops
    //
#if 1
    if (op >= 0)
    {
        /*Initialize the $gp register for sdata and sbss */
        printf("\n\nstart changing from addr: 0x%x\n", adst);
        printf("gp_ptr=0x%x ", gp_ptr);

        // update global_pointer
        set_low(code, adst+0, gp_ptr >> 16);        // modify the lui opcode
        set_low(code, adst+4, gp_ptr & 0xffff);     // modify the ori opcode

        // update pointer about .data
        // line 36, 40, 44, 48, 52, 58 in binFile
        // adst = 8, 12, 16, 20, 24, 28
        printf("instructionAddress=0x%x instructionLength=0x%x\n", \
            instructionAddress, instructionLength);
        printf("rodata_start_addr=0x%x rodata_end_addr=0x%x rodata_codeLength=0x%x\n", \
            rodataAddress, rodataAddress + rodataLength, rodataLength);
        printf("data_start_bin_addr=0x%x data_end_bin_addr=0x%x dataLength=0x%x data_addr_sram=0x%x\n", \
            data_start_bin, data_end_bin, dataLength, data_addr);
        set_low(code, adst+8, data_start_bin >> 16);
        set_low(code, adst+12, data_start_bin & 0xffff);
        set_low(code, adst+16, data_end_bin >> 16);
        set_low(code, adst+20, data_end_bin & 0xffff);
        set_low(code, adst+24, data_addr >> 16);
        set_low(code, adst+28, data_addr & 0xffff);

        // update pointer about .bss
        // line 106, 110, 114, 118 in binFile
        // adst = 76, 80, 84, 88
        printf("sbss=0x%x bss_end=0x%x\ncodeLength=0x%x ", bss_start, bss_end, codeLength);
        set_low(code, adst+76, bss_start >> 16);
        set_low(code, adst+80, bss_start & 0xffff);
        set_low(code, adst+84, bss_end >> 16);
        set_low(code, adst+88, bss_end & 0xffff);

        // Set stack pointer
        // line 122, 126 in binFile
        // adst = 92, 96
        if(elfHeader->e_entry < 0x10000000)     // root mode
        {
            stack_pointer = bss_end + 512;
            printf("\nstack pointer is +512 byte from bss_end\n");
        }
        else   // user mode
        {
            // stack_pointer = bss_end + 1024 * 1;
            stack_pointer = 0x01001f00;
            printf("\nstack pointer is +1024*1 byte from bss_end\n");
        }
        stack_pointer &= ~7;
        printf("SP=0x%lx\n", stack_pointer);
        printf("DCA size=4kx32 -> 0 - 3FFFF\n");
        set_low(code, adst+92, stack_pointer >> 16);
        set_low(code, adst+96, stack_pointer & 0xffff);
    }
#endif

    /*write out test.bin, code */
    strcpy(binFileName, inFileName);
    strcat(binFileName, ".bin");
    binFile = fopen(binFileName, "wb");
    fwrite(code, binLength, 1, binFile);
    fclose(binFile);

    /*write out test2.bin, rodata */
    strcpy(rodataBinFileName, inFileName);
    strcat(rodataBinFileName, "_rodata.bin");
    rodataBin = fopen(rodataBinFileName, "wb");
    fwrite(rodataCode, rodataLength, 1, rodataBin);
    fclose(rodataBin);

    // output data bin
    strcpy(dataBinFileName, inFileName);
    strcat(dataBinFileName, "_data.bin");
    dataBin = fopen(dataBinFileName, "wb");
    fwrite(dataCode, dataLength, 1, dataBin);
    fclose(dataBin);

    /*write out code.txt, code */
    strcpy(txtFileName, inFileName);
    strcat(txtFileName, ".txt");
    txtFile = fopen(txtFileName, "w");
    for(i = 0; i <= binLength; i += 4)
    {
        d = ntohl(*(uint32 *)(code + i));
        fprintf(txtFile, "%8.8x\n", d);
    }
    fclose(txtFile);

    /*write out rodataCode.txt, rodata */
    strcpy(rodataTxtFileName, inFileName);
    strcat(rodataTxtFileName, "_rodata.txt");
    rodataTxt = fopen(rodataTxtFileName, "w");
    for(i = 0; i <= rodataLength; i += 4)
    {
        d = ntohl(*(uint32 *)(rodataCode + i));
        fprintf(rodataTxt, "%8.8x\n", d);
    }
    fclose(rodataTxt);

    // output data.txt
    strcpy(dataTxtFileName, inFileName);
    strcat(dataTxtFileName, "_data.txt");
    dataTxt = fopen(dataTxtFileName, "w");
    for(i = 0; i <= dataLength; i += 4)
    {
        d = ntohl(*(uint32 *)(dataCode + i));
        fprintf(dataTxt, "%8.8x\n", d);
    }
    fclose(dataTxt);

    /*write out code.coe file*/
    strcpy(coeFileName, inFileName);
    strcat(coeFileName, ".coe");
    coefile = fopen(coeFileName, "w");
    fprintf(coefile, "memory_initialization_radix = 16;\n");
    fprintf(coefile, "memory_initialization_vector =\n");
    for(i = 0; i < codeLength; i += 4)
    {
        d = ntohl(*(uint32 *)(code + i));
        fprintf(coefile, "%8.8x\n", d);
    }
    d = ntohl(*(uint32 *)(code + codeLength));
    fprintf(coefile, "%8.8x;\n", d);
    fclose(coefile);

    strcpy(dataBinFileName, inFileName);
    strcat(dataBinFileName, "_data.bin");


    free(buf);
    printf("code codeLength=%d=0x%x\n", codeLength, codeLength);
    printf("rodata codeLength=%d=0x%x\n", rodataLength, rodataLength);
    printf("data codeLength=%d=0x%x\n", dataLength, dataLength);
    printf("bin codeLength=%d=0x%x\n", binLength, binLength);

    return 0;
}

#if DEBUG
    //This is here to determine what __BYTE_ORDER is set to in netinet/in.h.
    // Not in original code
    #if __DARWIN_BYTE_ORDER == BIG_ENDIAN
    #warning BIG ENDIAN BYTE ORDER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #endif
    //This is here to determine what __BYTE_ORDER is set to in netinet/in.h.
    // Not in original code
    #if __DARWIN_BYTE_ORDER == LITTLE_ENDIAN
    #warning YAY LITTLE ENDIAN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    #endif
#endif
