/**
* @file elf.c
* @author Zhirui Dai
* @date 16 Jul 2018
* @copyright 2018 Zhirui
* @brief ELF(Executable Linking Format)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "elf.h"

void Elf_Reader_printFileHeader(Elf32_Ehdr *header)
{
    printf("File header:\n");
    // Print the file class
    printf("\tELF Identification:\n");
    printf("\t\tMagic:                         ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    putchar('\n');
    printf("\t\tFile class:                    ");
    switch (Elf_Reader_elfFileClass(header)) {
        case ELFCLASSNONE:
            printf("NONE\n");
            break;
        case ELFCLASS32:
            printf("32-bit\n");
            break;
        case ELFCLASS64:
            printf("64-bit\n");
            break;
    }
    
    // Print the encoding type
    printf("\t\tData encoding type:            ");
    switch (Elf_Reader_fileDataEncodingType(header)) {
        case ELFDATANONE:
            printf("NONE\n");
            break;
        case ELFDATA2LSB:
            printf("Little endian\n");
            break;
        case ELFDATA2MSB:
            printf("Big endian\n");
            break;
    }
    
    // Print the elf version
    printf("\t\tELF Version:                   ");
    switch (Elf_Reader_elfVersion_FromIndent(header)) {
        case EV_NONE:
            printf("NONE\n");
            break;
        case EV_CURRENT:
            printf("Current\n");
            break;
    }
    
    // Print elf file type
    printf("\tELF file type:                     ");
    switch ((ELF_TYPE_T)header->e_type) {
        case ET_NONE:
            printf("No file type\n");
            break;
        case ET_REL:
            printf("Relocatable file\n");
            break;
        case ET_EXEC:
            printf("Executable file\n");
            break;
        case ET_DYN:
            printf("Shared object file\n");
            break;
        case ET_CORE:
            printf("Core file\n");
            break;
        case ET_LOPROC:
            printf("Processor-specific\n");
            break;
        case ET_HIPROC:
            printf("Processor-specific\n");
            break;
    }
    
    // print machine
    printf("\tMachine:                           ");
    switch ((ELF_MACHINE_T)header->e_machine) {
        case EM_NONE:
            printf("No machine\n");
            break;
        case EM_M32:
            printf("AT&T WE 32100\n");
            break;
        case EM_SPARC:
            printf("SPARC\n");
            break;
        case EM_386:
            printf("Intel 80386\n");
            break;
        case EM_68K:
            printf("Motorola 68000\n");
            break;
        case EM_88K:
            printf("Motorola 88000\n");
            break;
        case EM_860:
            printf("Intel 80860\n");
            break;
        case EM_MIPS:
            printf("MIPS RS3000\n");
            break;
        default:
            printf("Unknown: %d\n", header->e_machine);
            break;
    }
    
    // print elf version
    printf("\tELF Version:                       ");
    switch ((ELF_VERSION_T)header->e_version) {
        case EV_NONE:
            printf("NONE\n");
            break;
        case EV_CURRENT:
            printf("1(Current)\n");
            break;
    }
    
    // print other properties
    printf("\tEntry point address:               0x%x\n", header->e_entry);
    printf("\tOffset of 1st program header:      %d(bytes)\n", header->e_phoff);
    printf("\tFlags:                             0x%08x\n", header->e_flags);
    printf("\tFileHeader size:                   %d(bytes)\n", header->e_ehsize);
    printf("\tELF program header size:           %d(bytes)\n", header->e_phentsize);
    printf("\tNumber of program headers:         %d\n", header->e_phnum);
    printf("\tELF section header size:           %d(bytes)\n", header->e_shentsize);
    printf("\tNumber of section headers:         %d\n", header->e_shnum);
    printf("\tSection header string table index: %d\n", header->e_shstrndx);
}

void Elf_Reader_printSectionHeader(Elf32_Shdr *section, char *strTable)
{
    printf("\t\tSection name:                       %s(%d)\n", (char*)strTable + section->sh_name, section->sh_name);
    printf("\t\tSection type:                       ");
    switch ((SH_TYPE_T)section->sh_type) {
        case SHT_NULL:
            printf("SHT_NULL\n");
            break;
        case SHT_PROGBITS:
            printf("SHT_PROGBITS(Program instructions)\n");
            break;
        case SHT_STMTAB:
            printf("STMTAB(Symbol Table)\n");
            break;
        case SHT_STRTAB:
            printf("STRTAB(String Table)\n");
            break;
        case SHT_RELA:
            printf("RELA(Relocation with explicit addends)\n");
            break;
        case SHT_HASH:
            printf("HASH(Symbol hash table)\n");
            break;
        case SHT_DYNAMIC:
            printf("DYNAMIC(Dymanic linking)\n");
            break;
        case SHT_NOTE:
            printf("NOTE(Information for marking the file)\n");
            break;
        case SHT_NOBITS:
            printf("NOBITS(Contains no bits)\n");
            break;
        case SHT_REL:
            printf("REL(Relocation without explicit addends)\n");
            break;
        case SHT_SHLIB:
            printf("SHT_SHLIB(Unspecified semantics)\n");
            break;
        case SHT_DYNSYM:
            printf("DYNSYM(Dymanic linking symbol table)\n");
            break;
        case SHT_HIPROC:
            printf("HIPROC(Reserved for processor-specific semantics)\n");
            break;
        case SHT_LOPROC:
            printf("LOPROC(Reserved for processor-specific semantics)\n");
            break;
        case SHT_LOUSER:
            printf("LOUSER(Lower bound of the range of indexes reserved for application program)\n");
            break;
        case SHT_HIUSER:
            printf("HIUSER(Upper bound of the range of indexes reserved for application program)\n");
            break;
        case SHT_GNU_ATTRIBUTES:
            printf("GNU_ATTRIBUTES\n");
            break;
        case SHT_NUM:
            printf("NUM\n");
            break;
        case SHT_LOOS:
            printf("LOOS\n");
            break;
        case SHT_GROUP:
            printf("GROUP\n");
            break;
        case SHT_FINI_ARRAY:
            printf("FINI_ARRAY\n");
            break;
        case SHT_INIT_ARRAY:
            printf("INIT_ARRAY\n");
            break;
        case SHT_SYMTAB_SHNDX:
            printf("SYMTAB_SHNDX\n");
            break;
        case SHT_PREINIT_ARRAY:
            printf("PREINIT_ARRAY\n");
            break;
        case SHT_MIPS_ABIFLAGS:
            printf("MIPS_ABIFLAGS\n");
            break;
        case SHT_MIPS_REGINFO:
            printf("MIPS_REGINFO\n");
            break;
        case SHT_MIPS_CONFLICT:
            printf("MIPS_CONFLICT\n");
            break;
        case SHT_MIPS_GPTAB:
            printf("MIPS_GPTAB\n");
            break;
        case SHT_MIPS_UCODE:
            printf("MIPS_UCODE\n");
            break;
        case SHT_MIPS_DEBUG:
            printf("MIPS_DEBUG\n");
            break;
        default:
            printf("Unknown 0x%x\n", section->sh_type);
            break;
    }
    
    printf("\t\tSection flags:                      ");
    if (section->sh_flags & SHF_WRITE) { printf("WRITE "); }
    if (section->sh_flags & SHF_ALLOC) { printf("ALLOC "); }
    if (section->sh_flags & SHF_EXECINSTR) { printf("EXECINSTR "); }
    if (section->sh_flags & SHF_MASKPROC) { printf("Processor_specific "); }
    if (section->sh_flags & SHF_MERGE) { printf("MERGE "); }
    if (section->sh_flags & SHF_STRINGS) { printf("STRINGS "); }
    if (section->sh_flags & SHF_INFO_LINK) { printf("INFO_LINK "); }
    if (section->sh_flags & SHF_LINK_ORDER) { printf("LINK_ORDER "); }
    if (section->sh_flags & SHF_OS_NONCONFORMING) { printf("OS_NONCONFORMING "); }
    if (section->sh_flags & SHF_GROUP) { printf("GROUP "); }
    if (section->sh_flags & SHF_TLS) { printf("TLS "); }
    if (section->sh_flags & SHF_MASKOS) { printf("MASKOS "); }
    if (section->sh_flags & SHF_ORDERED) { printf("ORDERED "); }
    if (section->sh_flags & SHF_EXCLUDE) { printf("EXCLUDE "); }
    printf("(0x%x)\n", section->sh_flags);
    
    printf("\t\tMemory address:                     ");
    if (section->sh_addr > 0) {
        printf("0x%x\n", section->sh_addr);
    } else {
        printf("NONE\n");
    }
    
    printf("\t\tOffset of section data:             %d(bytes) from the file's 1st byte\n", section->sh_offset);
    printf("\t\tSection data size:                  %d(bytes)\n", section->sh_size);
    printf("\t\tSection header table index link:    0x%x\n", section->sh_link);
    printf("\t\tSection extra information:          0x%x\n", section->sh_info);
    printf("\t\tAddress alignment constraints:      %d\n", section->sh_addralign);
    printf("\t\tSize of each entry in the table:    %d(0=NONE)\n", section->sh_entsize);
//    putchar('\n');
}

void Elf_Reader_printProgramHeader(Elf32_Phdr *program)
{
    printf("\t\tHeader type:                        ");
    switch ((PROGRAM_TYPE_T)program->p_type) {
        case PT_NULL:
            printf("NULL\n");
            break;
        case PT_LOAD:
            printf("LOAD(Loadable segment)\n");
            break;
        case PT_DYNAMIC:
            printf("DYNAMIC\n");
            break;
        case PT_INTERP:
            printf("INTERP\n");
            break;
        case PT_NOTE:
            printf("NOTE\n");
            break;
        case PT_SHLB:
            printf("SHLB\n");
            break;
        case PT_PHDR:
            printf("PHDR\n");
            break;
        case PT_LOPROC:
            printf("MIPS_REGINFO | LOPROC(Processor-specific semantics)\n");
            break;
        case PT_HIPROC:
            printf("HIPROC(Processor-specific semantics)\n");
            break;
        case PT_HIOS:
            printf("HIOS(inclusive reserved ranges for operating system (processor) specific semantics)\n");
            break;
        case PT_LOOS:
            printf("LOOS(inclusive reserved ranges for operating system (processor) specific semantics)\n");
            break;
        case PT_MIPS_ABIFLAGS:
            printf("MIPS_ABIFLAGS\n");
            break;
        default:
            printf("UNKNOWN(0x%x)\n", program->p_type);
            break;
    }
    
    printf("\t\tOffset from the file's 1st byte:    %d(bytes)\n", program->p_offset);
    printf("\t\tVirtual memory address:             0x%x\n", program->p_vaddr);
    printf("\t\tPhysical memory address:            0x%x\n", program->p_paddr);
    printf("\t\tSize of the segment in the file:    %d(bytes)\n", program->p_filesz);
    printf("\t\tSize of the segment in the memory:  %d(bytes)\n", program->p_memsz);
    printf("\t\tFlags:                              0x%x\n", program->p_flags);
    printf("\t\tAlisgn:                             %d\n", program->p_align);
}

ELF_T Elf_Reader_loadElf(char* fileName) {
    ELF_T elf;
    elf.fileName = fileName;
    // open the elf file
    FILE* elfFilePointer = fopen(elf.fileName, "rb");
    if (elfFilePointer == NULL) {
        fprintf(stderr, "Fail to open %s!\n", elf.fileName);
        exit(EXIT_FAILURE);
    }
    // get the elf file size
    elf.fileSize = ftell(elfFilePointer);
    fseek(elfFilePointer, 0, SEEK_END);     // seek to end of file
    elf.fileSize = ftell(elfFilePointer);   // get current file pointer
    fseek(elfFilePointer, 0, SEEK_SET);     // seek back to beginning of file
    // prepare the buffer for storing the elf file
    elf.buf = malloc(elf.fileSize);
    if (elf.buf == NULL) {
        fprintf(stderr, "Fail to malloc!\n");
        exit(EXIT_FAILURE);
    }
    // load data
    size_t size = fread(elf.buf, 1, elf.fileSize, elfFilePointer);
    fclose(elfFilePointer);
    assert(size == elf.fileSize);
    // analyse elf data
    elf.fileHeader = (Elf32_Ehdr*)elf.buf;
    Elf_Reader_loadSectionHeaders(&elf);
    Elf_Reader_loadProgramHeaders(&elf);
    elf.regInfo = Elf_Reader_getMIPSRegInfo(elf);
    elf.strTable = Elf_Reader_getStringTable(elf);
    return elf;
}

