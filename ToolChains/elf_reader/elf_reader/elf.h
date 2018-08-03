/**
* @file elf.h
* @author Zhirui Dai
* @date 16 Jul 2018
* @copyright 2018 Zhirui
* @brief ELF(Executable Linking Format)
*/

#ifndef __ELF_H__
#define __ELF_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
    // ELF file structure
    |: -------------------- :|
    |      ELF header        |
    |------------------------|
    | Program header table   |
    |------------------------|
    |       Segment  1       |
    |------------------------|
    |       Segment  2       |
    |------------------------|
    |       ..........       |
    |------------------------|
    |       Segment  n       |
    |------------------------|
    |  Section header table  |
    |       (optional)       |
    |:----------------------:|
 */

typedef uint32_t Elf32_Addr;        /*! Unsigned program address */
typedef uint16_t Elf32_Half;        /*! Unsigned medium integer */
typedef uint32_t Elf32_Off;         /*! Unsigned file offset */
typedef int32_t  Elf32_Sword;       /*! Signed large integer */
typedef uint32_t Elf32_Word;        /*! Unsigned large integer */

// MARK:- ELF Header

#define EI_NIDENT   16              /*! The size of the ELF Identification property of ELF Header */

typedef struct {
    /*! Mark the file as an object file and provide machine-independent data
        with which to decode and interpret the file's contents */
    unsigned char   e_ident[EI_NIDENT];
    Elf32_Half      e_type;         /*! The object file type. */
    Elf32_Half      e_machine;      /*! This member’s value specifies the required architecture for an individual file. */
    Elf32_Word      e_version;      /*! This member identifies the object file version. */
    Elf32_Addr      e_entry;        /*! This member gives the virtual address to which the system first transfers control, thus
                                     starting the process. If the file has no associated entry point, this member holds zero. */
    Elf32_Off       e_phoff;        /*! the program header table’s file offset in bytes. */
    Elf32_Off       e_shoff;        /*! the section header table’s file offset in bytes. */
    Elf32_Word      e_flags;        /*! This member holds processor-specific flags associated with the file.
                                     Flag names take the form EF_machine_flag. */
    Elf32_Half      e_ehsize;       /*! This member holds the ELF header’s size in bytes. */
    Elf32_Half      e_phentsize;    /*! This member holds the size in bytes of one entry in the file’s program header table; all
                                     entries are the same size. */
    Elf32_Half      e_phnum;        /*! This member holds the number of entries in the program header table. */
    Elf32_Half      e_shentsize;    /*! This member holds a section header’s size in bytes. A section header is one entry in the
                                     section header table; all entries are the same size. */
    Elf32_Half      e_shnum;        /*! holds the number of entries in the section header table. */
    Elf32_Half      e_shstrndx;     /*! This member holds the section header table index of the entry associated with the section
                                     name string table. If the file has no section name string table, this member holds the value
                                     #SHN_UNDEF. */
} Elf32_Ehdr;

// Position of different properties in the e_indent
typedef enum {
    EI_CLASS   = 4,     /*! File class */
    EI_DATA    = 5,     /*! Data encoding */
    EI_VERSION = 6,     /*! File version */
    EI_PAD     = 7      /*! Start of padding types */
} E_INDENT_POS;

typedef enum {
    ELFCLASSNONE = 0,   /*! Invalid class */
    ELFCLASS32   = 1,   /*! 32-bit objects */
    ELFCLASS64   = 2    /*! 64-bit objects */
} EI_CLASS_T;

typedef enum {
    ELFDATANONE = 0,    /*! Invalid data encoding */
    ELFDATA2LSB = 1,    /*! Little endian */
    ELFDATA2MSB = 2     /*! Big endian */
} EI_DATA_T;

typedef enum {
    ET_NONE     = 0,        /*! No file type */
    ET_REL      = 1,        /*! Relocatable file */
    ET_EXEC     = 2,        /*! Executable file */
    ET_DYN      = 3,        /*! Shared object file */
    ET_CORE     = 4,        /*! Core file */
    ET_LOPROC   = 0xff00,   /*! Processor-specific */
    ET_HIPROC   = 0xffff    /*! Processor-specific */
} ELF_TYPE_T;

typedef enum {
    EF_MIPS_NOREORDER   = 0x1,          /*! directive in an assembly language source contributes to the object module. */
    EF_MIPS_PIC         = 0x2,          /*! This bit is asserted when the file contains posi- tion-independent code that can be
                                         relocated in memory. */
    EF_MIPS_CPIC        = 0x4,          /*! This bit is asserted when the file contains code that follows standard calling sequence
                                         rules for calling position-independent code. The EF_MIPS_PIC and EF_MIPS_CPIC flags must be
                                         mutually exclusive.*/
    EF_MIPS_ARCH        = 0xf0000000    /*! The integer value formed by these four bits iden- tify extensions to the basic MIPS I
                                         architecture. */
} ELF_FLAG_T;

typedef enum {
    EM_NONE     = 0,        /*! No machine */
    EM_M32      = 1,        /*! AT&T WE 32100 */
    EM_SPARC    = 2,        /*! SPARC */
    EM_386      = 3,        /*! Intel 80386 */
    EM_68K      = 4,        /*! Motorola 68000 */
    EM_88K      = 5,        /*! Motorola 88000 */
    EM_860      = 7,        /*! Intel 80860 */
    EM_MIPS     = 8         /*! MIPS RS3000 */
} ELF_MACHINE_T;

typedef enum {
    EV_NONE     = 0,        /*! Invalid version */
    EV_CURRENT  = 1         /*! Current version */
} ELF_VERSION_T;

// MARK:- ELF Section

typedef struct {
    Elf32_Word  sh_name;        /*! specifies the name of the section. Its value is an index into the section header string table
                                 section */
    Elf32_Word  sh_type;        /*! categorizes the section’s contents and semantics, see #SH_TYPE_T */
    Elf32_Word  sh_flags;       /*! support 1-bit flags that describe miscellaneous attributes, see #SH_FLAG_T */
    Elf32_Addr  sh_addr;        /*! If the section will appear in the memory image of a process, this member gives the address at
                                 which the section’s first byte should reside. Otherwise, the member contains 0. */
    Elf32_Off   sh_offset;      /*! gives the byte offset from the beginning of the file to the first byte in the section. */
    Elf32_Word  sh_size;        /*! gives the section’s size in bytes. Unless the section type is SHT_NOBITS, the section occupies
                                 sh_size bytes in the file. A section of type SHT_NOBITS may have a non-zero size, but it occupies
                                 no space in the file.*/
    Elf32_Word  sh_link;        /*! holds a section header table index link, whose interpretation depends on the section type,
                                 see TIS 1-13 */
    Elf32_Word  sh_info;        /*! holds extra information, whose interpretation depends on the section type, see TIS 1-13. */
    Elf32_Word  sh_addralign;   /*! Some sections have address alignment constraints. For example, if a section holds a doubleword,
                                 the system must ensure doubleword alignment for the entire section. That is, the value of sh_addr
                                 must be congruent to 0, modulo the value of sh_addralign. */
    Elf32_Word  sh_entsize;     /*! Some sections hold a table of fixed-size entries, such as a symbol table. For such a section,
                                 this member gives the size in bytes of each entry. The member contains 0 if the section does not
                                 hold a table of fixed-size entries. */
} Elf32_Shdr;

/*
 From <ELF: Executable and Linkable Format, Portable Formats Specification, Version 1.1 > of Tool Interface Standards(TIS) :
 
 An object file’s section header table lets one locate all the file’s sections. The section header table is an array of Elf32_Shdr
 structures as described below (here it is defined above).
 
 A section header table index is a subscript into this array. The ELF header’s e_shoff member gives the byte offset from the beginning
 of the file to the sec- tion header table; e_shnum tells how many entries the section header table contains; e_shentsize gives the
 size in bytes of each entry.
 
 Sections contain all information in an object file, except the ELF header, the program header table, and the section header table.
 Moreover, object files’ sections satisfy several conditions.
 - Every section in an object file has exactly one section header describing it. Section headers may exist that do not have a section.
 - Each section occupies one contiguous (possibly empty) sequence of bytes within a file.
 - Sections in a file may not overlap. No byte in a file resides in more than one section.
 - An object file may have inactive space. The various headers and the sections might not ‘‘cover’’ every byte in an object file.
    The contents of the inactive data are unspecified.
 */
typedef enum {
    SHN_UNDEF       = 0,        /*! Undefined, missing, irrelevant or otherwise meaningless section */
    SHN_LORESERVE   = 0xff00,   /*! Lower bound of the range of reserved indecies */
    SHN_LOPROC      = 0xff00,   /*! Reserved by processor */
    SHN_HIPROC      = 0xff00,   /*! Reserved by processor */
    SHN_ABS         = 0xff1f,   /*! Absolute values for the corresponding reference, not affected by relocation */
    SHN_COMMON      = 0xfff1,   /*! Symbols defined relative to this section are common symbols, such as FORTRAN COMMON or unallocated
                                 C external variables */
    SHN_HIRESERVE   = 0xffff,   /*! upper bound of the range of reserved indecies */
    /*! The system reserves indecies between SHN_LORESERVE and SHN_HIRESERVE, that is, the section header table does not contain
     entries for the reserved indecies. */
    // MIPS: See http://www.sco.com/developers/devspecs/mipsabi.pdf 4-3
    SHN_MIPS_ACOMMON    = 0xff00,
    SHN_MIPS_TEXT       = 0xff01,
    SHN_MIPS_DATA       = 0xff02,
    SHN_MIPS_SCOMMON    = 0xff03,
    SHN_MIPS_SUNDEFINED = 0xff04
} SPECIAL_SECTION_INDEX_T;

/// Section header type enumeration.
typedef enum {
    SHT_NULL        = 0,            /*! Some sections hold a table of fixed-size entries, such as a symbol table. For such a section,
                                     this member gives the size in bytes of each entry. The member contains 0 if the section does not
                                     hold a table of fixed-size entries. */
    SHT_PROGBITS    = 1,            /*! The section holds information defined by the program, whose format and meaning are determined
                                     solely by the program. */
    SHT_STMTAB      = 2,            /*! These sections hold a symbol table. Currently, an object file may have only one sec- tion of
                                     each type, but this restriction may be relaxed in the future. Typically, SHT_SYMTAB provides
                                     symbols for link editing, though it may also be used for dynamic linking. As a complete symbol
                                     table, it may contain many symbols unneces- sary for dynamic linking. Consequently, an object file
                                     may also contain a SHT_DYNSYM section, which holds a minimal set of dynamic linking symbols, to
                                     save space. */
    SHT_STRTAB      = 3,            /*! The section holds a string table. An object file may have multiple string table sections. */
    SHT_RELA        = 4,            /*! The section holds relocation entries with explicit addends, such as type Elf32_Rela for
                                     the 32-bit class of object files. An object file may have multiple relocation sections. */
    SHT_HASH        = 5,            /*! The section holds a symbol hash table. All objects participating in dynamic linking must
                                     contain a symbol hash table. Currently, an object file may have only one hash table, but this
                                     restriction may be relaxed in the future. */
    SHT_DYNAMIC     = 6,            /*! The section holds information for dynamic linking. Currently, an object file may have only one
                                     dynamic section, but this restriction may be relaxed in the future. See TIS 1-13  */
    SHT_NOTE        = 7,            /*! The section holds information that marks the file in some way. */
    SHT_NOBITS      = 8,            /*! A section of this type occupies no space in the file but otherwise resembles SHT_PROGBITS.
                                     Although this section contains no bytes, the sh_offset member contains the conceptual file offset.
                                     */
    SHT_REL         = 9,            /*! The section holds relocation entries without explicit addends, such as type Elf32_Rel for the
                                     32-bit class of object files. An object file may have multiple reloca- tion sections. */
    SHT_SHLIB       = 10,           /*! This section type is reserved but has unspecified semantics. Programs that contain a section of
                                     this type do not conform to the ABI. */
    SHT_DYNSYM      = 11,           /*! See SHT_SMTAB */
    SHT_LOPROC      = 0x70000000,   /*! reserved for processor-specific semantics. */
    SHT_HIPROC      = 0x7fffffff,   /*! reserved for processor-specific semantics. */
    SHT_LOUSER      = 0x80000000,   /*! This value specifies the lower bound of the range of indexes reserved for application programs.
                                     */
    SHT_HIUSER      = 0xffffffff,   /*! This value specifies the upper bound of the range of indexes reserved for application programs.
                                     */
    // GNU
    SHT_GNU_ATTRIBUTES  = 0x6ffffff5,
    // MIPS
    SHT_MIPS_LIBLIST    = 0x70000000,
    SHT_MIPS_CONFLICT   = 0x70000002,
    SHT_MIPS_GPTAB      = 0x70000003,
    SHT_MIPS_UCODE      = 0x70000004,
    SHT_MIPS_DEBUG      = 0x70000005,
    SHT_MIPS_REGINFO    = 0x70000006,
    SHT_MIPS_ABIFLAGS   = 0x7000002a,
    // Other
    SHT_INIT_ARRAY      = 0xE,      /*! Array of constructors */
    SHT_FINI_ARRAY      = 0xF,      /*! Array of destructors */
    SHT_PREINIT_ARRAY   = 0x10,     /*! Array of pre-constructors */
    SHT_GROUP           = 0x11,     /*! Section group */
    SHT_SYMTAB_SHNDX    = 0x12,     /*! Extended section indices */
    SHT_NUM             = 0x13,     /*! Number of defined types. */
    SHT_LOOS            = 0x60000000    /*! Start OS-specific. */
} SH_TYPE_T;

/// Section header flag enumeration.
typedef enum {
    SHF_WRITE       = 0x1,          /*! The section contains data that should be writable during process execution. */
    SHF_ALLOC       = 0x2,          /*! The section occupies memory during process execution.  */
    SHF_EXECINSTR   = 0x4,          /*! The section contains executable machine instructions. */
    SHF_MASKPROC    = 0xf0000000,   /*! All bits included in this mask are reserved for processor-specific semantics. */
    // MIPS
    SHF_MIPS_GPREL  = 0x10000000,
    // Other non-public flags
    SHF_MERGE       = 0x10,         /*! Might be merged */
    SHF_STRINGS     = 0x20,         /*! Contains nul-terminated strings */
    SHF_INFO_LINK   = 0x40,         /*! 'sh_info' contains SHT index */
    SHF_LINK_ORDER  = 0x80,         /*! Preserve order after combining */
    SHF_OS_NONCONFORMING    = 0x100,    /*! Non-standard OS specific handling required */
    SHF_GROUP       = 0x200,        /*! Section is member of a group */
    SHF_TLS         = 0x400,        /*! Section hold thread-local data */
    SHF_MASKOS      = 0xff00000,    /*! OS-specific */
    SHF_ORDERED     = 0x4000000,    /*! Special ordering requirement (Solaris) */
    SHF_EXCLUDE     = 0x8000000     /*! Section is excluded unless referenced or allocated (Solaris) */
} SH_FLAG_T;

/*
 Special Sections
 |       Name      |       Type      |          Atttibutes         |
 |  .bss           |  SHT_NOBITS     |  SHF_ALLOC + SHF_WRITE      |
 |  .comment       |  SHT_PROGBITS   |       none                  |
 |  .data          |  SHT_PROGBITS   |  SHF_ALLOC + SHF_WRITE      |
 |  .data1         |  SHT_PROGBITS   |  SHF_ALLOC + SHF_WRITE      |
 |  .debug         |  SHT_PROGBITS   |       none                  |
 |  .dynamic       |  SHT_DYNAMIC    |  See TIS 1-14               |
 |  .dynstr        |  SHT_STRTAB     |  SHF_ALLOC                  |
 |  .dynsym        |  SHT_DYNSYM     |  SHF_ALLOC                  |
 |  .fini          |  SHT_PROGBITS   |  SHF_ALLOC + SHF_EXECINSTR  |
 |  .got           |  SHT_PROGBITS   |  See TIS 1-14               |
 |  .hash          |  SHT_HASH       |  SHF_ALLOC                  |
 |  .init          |  SHT_PROGBITS   |  SHF_ALLOC + SHF_EXECINSTR  |
 |  .interp        |  SHT_PROGBITS   |  See TIS 1-14               |
 |  .line          |  SHT_PROGBITS   |       none                  |
 |  .note          |  SHT_NOTE       |       none                  |
 |  .plt           |  SHT_PROGBITS   |  See TIS 1-14               |
 |  .rel(name)     |  SHT_REL        |  See TIS 1-14               |
 |  .rela(name)    |  SHT_RELA       |  See TIS 1-15               |
 |  .rodata        |  SHT_PROGBITS   |  SHF_ALLOC                  |
 |  .rodata1       |  SHT_PROGBITS   |  SHF_ALLOC                  |
 |  .shstrtab      |  SHT_STRTAB     |       none                  |
 |  .strtab        |  SHT_SYMTAB     |  See TIS 1-15               |
 |  .symtab        |  SHT_SYMTAB     |  See TIS 1-15               |
 |  .text          |  SHT_PROGBITS   |  SHT_ALLOC + SHF_EXECINSTR  |
 */
typedef enum {
    _bss        = 0,        /*! This section holds uninitialized data that contribute to the program’s memory image. By definition,
                             the system initializes the data with zeros when the program begins to run. The section occupies no file
                             space, as indicated by the section type, SHT_NOBITS. */
    _comment,               /*! This section holds uninitialized data that contribute to the program’s memory image. By definition,
                             the system initializes the data with zeros when the program begins to run. The section occupies no file
                             space, as indicated by the section type, SHT_NOBITS. */
    _data, _datal,          /*! These sections hold initialized data that contribute to the program’s memory image. */
    _debug,                 /*! This section holds information for symbolic debugging. The contents are unspecified. */
    _dynamic,               /*! This section holds dynamic linking information. The section’s attributes will include the SHF_ALLOC
                             bit. Whether the SHF_WRITE bit is set is processor specific. */
    _dynstr,                /*! This section holds strings needed for dynamic linking, most commonly the strings that represent the
                             names associated with symbol table entries. */
    _dynsym,                /*! This section holds the dynamic linking symbol table */
    _fini,                  /*! This section holds executable instructions that contribute to the process termination code. That is,
                             when a program exits normally, the system arranges to execute the code in this section. */
    _got,                   /*! This section holds the global offset table. */
    _hash,                  /*! This section holds a symbol hash table. */
    _init,                  /*! This section holds executable instructions that contribute to the process initialization code.
                             That is, when a program starts to run, the system arranges to execute the code in this sec- tion before
                             calling the main program entry point  */
    _interp,                /*! This section holds the path name of a program interpreter. If the file has a loadable seg- ment that
                             includes the section, the section’s attributes will include the SHF_ALLOC bit; otherwise, that bit will
                             be off.  */
    _line,                  /*! This section holds line number information for symbolic debugging, which describes the correspondence
                             between the source program and the machine code. The contents are unspecified. */
    _note,                  /*! Note Section */
    _plt,                   /*! This section holds the procedure linkage table. */
    _rel, _rela,            /*! These sections hold relocation information */
    _rodata, _rodatal,      /*! These sections hold read-only data that typically contribute to a non-writable segment in the process
                             image. */
    _shstrtab,              /*! This section holds section names. */
    _strtab,                /*! This section holds strings, most commonly the strings that represent the names associated with symbol
                             table entries. If the file has a loadable segment that includes the symbol string table, the section’s
                             attributes will include the SHF_ALLOC bit; otherwise, that bit will be off. */
    _symtab,                /*! This section holds a symbol table, as ‘‘Symbol Table’’ in this section describes. If the file has a
                             loadable segment that includes the symbol table, the section’s attributes will include the SHF_ALLOC bit;
                             otherwise, that bit will be off. */
    _text,                  /*! executable instructions, of a program. */
    _sdata, _sbss, _lit8, _gptab, _conflict, _tdesc, _lit4, _reginfo, _liblist  /*! Pre-existing Extensions */
} SPECIAL_SECTION_T;

// MARK: Symbol Table
/// Symbol Table
typedef struct {
    Elf32_Word      st_name;    /*! This member holds an index into the object file’s symbol string table, which holds the character
                                 representations of the symbol names. If the value is non-zero, it represents a string table index
                                 that gives the symbol name. Otherwise, the symbol table entry has no name. */
    Elf32_Addr      st_value;   /*! This member gives the value of the associated symbol. */
    Elf32_Word      st_size;    /*! This member gives the size of the symbol. */
    unsigned char   st_info;    /*! The high 4 bits are for Symbol Binding and the low 4 bits are for Symbol Type. */
    unsigned char   st_other;   /*! This member currently holds 0 and has no defined meaning. */
    Elf32_Half      st_shndx;   /*! Every symbol table entry is ‘‘defined’’ in relation to some section; this member holds the
                                 relevant section header table index. */
} Elf32_Sym;

/*! A symbol table entry has the members from st_name to st_other set as 0 and st_shndx as SHN_UNDEF.
 struct Symbol_Table_Entry: Index 0 {
    st_name     = 0;
    st_value    = 0;
    st_size     = 0;
    st_info     = 0;
    st_other    = 0;
    st_shndex   = SHN_UNDEF;
 };
 */

/// High 4 bits of Elf32_Sym.st_info: Symbol table binding
typedef enum {
    STB_LOCAL   = 0,    /*! Local symbol, unvisible outside the object file. */
    STB_GLOBAL  = 1,    /*! Global symbol */
    STB_WEAK    = 2,    /*! Weak global symbol, has a lower procedence than Global symbol. */
    STB_LOPROC  = 13,   /*! Reserved for processor semantics. */
    STB_HIPROC  = 15    /*! Reserved for processor semantics. */
} SYMBOL_TABLE_BINDING_T;

/// Low 4 bits of Elf32_Sym.st_info: Symbol table type
typedef enum {
    STT_NOTYPE  = 0,    /*! Not specified type. */
    STT_OBJECT  = 1,    /*! Data object, such as a variable, an array, etc. */
    STT_FUNC    = 2,    /*! A function or other executable code. */
    STT_SECTION = 3,    /*! For relocation. */
    STT_FILE    = 4,    /*! Conventionally, the symbol’s name gives the name of the source file associated with the object file.
                         A file symbol has STB_LOCAL binding, its section index is SHN_ABS, and it precedes the other STB_LOCAL
                         symbols for the file, if it is present. */
    STT_LOPROC  = 13,   /*! Reserved for processor semantics. */
    STT_HIPROC  = 15    /*! Reserved for processor semantics. */
} SYMBOL_TABLE_TYPE_T;

// MARK:- MIPS Register Information
/*!
 Register Information Structure
 @see http://www.sco.com/developers/devspecs/mipsabi.pdf 4-14
 */
typedef struct {
    Elf32_Word      ri_gprmask;     /*! This member contains a bit-mask of general registers used by the program. */
    Elf32_Word      ri_cprmask[4];  /*! This member contains the bit-mask of co-processor registers used by the program. */
    Elf32_Sword     ri_gp_value;    /*! This member contains the gp register value. */
} Elf32_RegInfo;

// MARK:- Relocation
typedef struct {
    Elf32_Addr  r_offset;   /*! This member gives the location at which to apply the relocation action. For a relocatable file,
                             the value is the byte offset from the beginning of the section to the storage unit affected by the
                             relocation. For an executable file or a shared object, the value is the virtual address of the storage
                             unit affected by the relocation. */
    Elf32_Word  r_info;     /*! This member gives both the symbol table index with respect to which the relocation must be made, and
                             the type of relocation to apply. */
} Elf32_Rel;

typedef struct {
    Elf32_Addr  r_offset;
    Elf32_Word  r_info;
    Elf32_Sword r_added;
} Elf32_Rela;

// TODO: Complete the relocation

// MARK:- Program Header
/*
 An executable or shared object file’s program header table is an array of structures, each describing a seg- ment or other
 information the system needs to prepare the program for execution. An object file segment contains one or more sections, as
 ‘Segment Contents’ describes below. Program headers are meaningful only for executable and shared object files. A file specifies
 its own program header size with the ELF header’s e_phentsize and e_phnum members
 */
typedef struct {
    Elf32_Word  p_type;     /*! This member tells what kind of segment this array element describes or how to interpret the array
                             element’s information.  */
    Elf32_Off   p_offset;   /*! This member gives the offset from the beginning of the file at which the first byte of the segment
                             resides. */
    Elf32_Addr  p_vaddr;    /*! This member gives the virtual address at which the first byte of the segment resides in memory. */
    Elf32_Addr  p_paddr;    /*! On systems for which physical addressing is relevant, this member is reserved for the segment’s
                             physical address. Because System V ignores physical addressing for applica- tion programs, this member
                             has unspecified contents for executable files and shared objects. */
    Elf32_Word  p_filesz;   /*! This member gives the number of bytes in the file image of the segment; it may be zero. */
    Elf32_Word  p_memsz;    /*! This member gives the number of bytes in the memory image of the segment; it may be zero. */
    Elf32_Word  p_flags;    /*! This member gives flags relevant to the segment. */
    Elf32_Word  p_align;    /*! This member gives the value to which the segments are aligned in memory and in the file. p_vaddr
                             should equal p_offset, modulo p_align. */
} Elf32_Phdr;

typedef enum {
    PT_NULL     = 0,            /*! The array element is unused; other members’ values are undefined. This type lets the program
                                 header table have ignored entries. */
    PT_LOAD     = 1,            /*! The array element specifies a loadable segment, described by p_filesz and p_memsz. */
    PT_DYNAMIC  = 2,            /*! The array element specifies dynamic linking information. */
    PT_INTERP   = 3,            /*! The array element specifies the location and size of a null-terminated path name to invoke as
                                 an interpreter. This segment type is meaningful only for executable files */
    PT_NOTE     = 4,            /*! The array element specifies the location and size of auxiliary information. */
    PT_SHLB     = 5,            /*! This segment type is reserved but has unspecified semantics. Programs that contain an array
                                 element of this type do not conform to the ABI. */
    PT_PHDR     = 6,            /*! The array element, if present, specifies the location and size of the program header table
                                 itself, both in the file and in the memory image of the program. */
    PT_LOPROC   = 0x70000000,   /*! Values in this inclusive range are reserved for processor-specific semantics. */
    PT_HIPROC   = 0x7fffffff,   /*! Values in this inclusive range are reserved for processor-specific semantics. */
    // Other
    PT_LOOS     = 0x60000000,
    PT_HIOS     = 0x6FFFFFFF,
    // MIPS
    PT_MIPS_REGINFO = 0x70000000,
    PT_MIPS_ABIFLAGS = 0x70000003,
} PROGRAM_TYPE_T;

// TODO: Program loading, Dynamic linking

// MARK:- ELF_Program
typedef struct {
    char            *fileName;
    unsigned long   fileSize;
    uint8_t         *buf;
    Elf32_Ehdr      *fileHeader;
    uint32_t        sectionHeaderNum;
    Elf32_Shdr      **sectionsHeaders;
    char            *strTable;
    uint32_t        programHeaderNum;
    Elf32_Phdr      **programHeaders;
    Elf32_RegInfo   *regInfo;
} ELF_T;

// MARK:- Functions
static const unsigned char MAGIC_NUMBER[] = {0x7f,'E','L','F'};

/**
 Tell if the file in the buffer is an ELF file.
 
 @param elf the buffer containing the submitted file.
 @return true for an ELF file, false for a non-ELF file.
 */
static inline bool Elf_Reader_isElfFile(ELF_T elf)
{
    return !memcmp(elf.fileHeader->e_ident, MAGIC_NUMBER, 4);
}

/**
 Read and check the class of the ELF file. Assert an error if the class is unknown.
 
 @param header the ELF file header.
 @return The class of the ELF file. #ELFCLASSNONE, #ELFCLASS32 or #ELFCLASS64.
 */
static inline EI_CLASS_T Elf_Reader_elfFileClass(const Elf32_Ehdr* header)
{
    int i = header->e_ident[EI_CLASS];
    if (i<0 || i>2) {
        fprintf(stderr, "Undefined elf file class!\n");
        exit(EXIT_FAILURE);
    }
    return i;
}

/**
 Read an check the data encoding type of the ELF file. Assert an error if the class is unknown.
 
 @param header the ELF file header.
 @return The data encoding type of the ELF file. #ELFDATANONE, #ELFDATA2LSB, or #ELFDATA2MSB.
 */
static inline EI_DATA_T Elf_Reader_fileDataEncodingType(const Elf32_Ehdr* header)
{
    int i = header->e_ident[EI_DATA];
    if (i<0 || i>2) {
        fprintf(stderr, "Undefined data encoding type!\n");
        exit(EXIT_FAILURE);
    }
    return i;
}

static inline ELF_VERSION_T Elf_Reader_elfVersion_FromIndent(const Elf32_Ehdr* header)
{
    int i = header->e_ident[EI_VERSION];
    if (i < 0 || i > 1) {
        fprintf(stderr, "Undefined elf version!\n");
        exit(EXIT_FAILURE);
    }
    return i;
}

static inline void Elf_Reader_checkElfVersion(const ELF_T elf)
{
    if (elf.fileHeader->e_version != elf.fileHeader->e_ident[EI_VERSION]) {
        fprintf(stderr, "The elf versions stored in e_version and e_ident[6] are different!\n");
        exit(EXIT_FAILURE);
    }
}

static inline void Elf_Reader_printFileSize(ELF_T elf)
{
    if (Elf_Reader_isElfFile(elf)) {
        printf("ELF file: %s,  size: %lu bytes\n", elf.fileName, elf.fileSize);
    } else {
        fprintf(stderr, "The file '%s' is not an ELF file!\n", elf.fileName);
        exit(EXIT_FAILURE);
    }
}

void Elf_Reader_printFileHeader(Elf32_Ehdr *header);

static inline void Elf_Reader_loadSectionHeaders(ELF_T *elf)
{
    elf->sectionHeaderNum = elf->fileHeader->e_shnum;
    elf->sectionsHeaders = (Elf32_Shdr**)malloc(sizeof(Elf32_Shdr*) * elf->fileHeader->e_shnum);
    memset(elf->sectionsHeaders, 0, elf->sectionHeaderNum * sizeof(Elf32_Shdr*));
    for (uint32_t i = 0; i < elf->fileHeader->e_shnum; i++) {
        elf->sectionsHeaders[i] = (Elf32_Shdr*)(elf->buf + elf->fileHeader->e_shoff + elf->fileHeader->e_shentsize * i);
    }
}

static inline Elf32_Shdr* Elf_Reader_getSctionHeader(ELF_T elf, uint32_t index)
{
    if (index > elf.fileHeader->e_shnum) {
        fprintf(stderr, "Index for section is out of range!\n");
        exit(EXIT_FAILURE);
    } else {
        return (Elf32_Shdr*)(elf.buf + elf.fileHeader->e_shoff + elf.fileHeader->e_shentsize * index);
    }
}

static inline char* Elf_Reader_getStringTable(ELF_T elf)
{
    if (elf.fileHeader->e_shstrndx == SHN_UNDEF) {
        fprintf(stderr, "The string table is undefined!\n");
        return NULL;
    } else {
        Elf32_Shdr *strSection = Elf_Reader_getSctionHeader(elf, elf.fileHeader->e_shstrndx);
        if (strSection->sh_offset > 0) {
            return (char*)(elf.buf + strSection->sh_offset);
        } else {
            return NULL;
        }
    }
}

static inline void Elf_Reader_printStringTable(ELF_T elf)
{
    printf("String Table:\n");
    char *strTable = Elf_Reader_getStringTable(elf);
    for(uint32_t i = 0; i < elf.fileHeader->e_shentsize; i++) {
        if (i % 10 == 0 && i > 0) {
            putchar('\n');
        }
        printf("%02x(%c)\t", *(strTable + i), *(strTable + i));
    }
    putchar('\n');
}

void Elf_Reader_printSectionHeader(Elf32_Shdr *section, char *strTable);

static inline void Elf_Reader_printAllSectionHeaders(ELF_T elf)
{
    printf("Section headers:\n");
    elf.strTable = Elf_Reader_getStringTable(elf);
    if (elf.strTable != NULL) {
        for (uint32_t i = 0; i < elf.sectionHeaderNum; i++) {
            printf("\tSection Header [%d]:\n", i);
            Elf_Reader_printSectionHeader(elf.sectionsHeaders[i], elf.strTable);
        }
    }
}

static inline Elf32_RegInfo* Elf_Reader_getMIPSRegInfo(const ELF_T elf)
{
    for (uint32_t i = 0; i < elf.sectionHeaderNum; i++) {
        if ((SH_TYPE_T)(elf.sectionsHeaders[i]->sh_type) == SHT_MIPS_REGINFO) {
            return (Elf32_RegInfo*)(elf.buf + elf.sectionsHeaders[i]->sh_offset);
        }
    }
    return NULL;
}

static inline void Elf_Reader_printMIPSRegInfo(const Elf32_RegInfo* regInfo)
{
    printf("Register Information:\n");
    printf("\tCPU Register Usage:             0x%x\n", regInfo->ri_gprmask);
    printf("\tCo-processor Register Usage:\n");
    for (uint32_t i = 0; i < 4; i++) {
        printf("\t\t[%d]:    0x%x\n", i, regInfo->ri_cprmask[i]);
    }
    printf("\tGlobal pointer:                 0x%x\n", regInfo->ri_gp_value);
}

static inline SYMBOL_TABLE_BINDING_T Elf_Reader_symtableTableBindingType(const Elf32_Sym table)
{
    return (table.st_info >> 4);
}

static inline SYMBOL_TABLE_TYPE_T Elf_Reader_symbolTableSymbolType(const Elf32_Sym table)
{
    return (table.st_info & 0xff);
}

static inline void Elf_Reader_loadProgramHeaders(ELF_T *elf)
{
    elf->programHeaderNum = elf->fileHeader->e_phnum;
    elf->programHeaders = (Elf32_Phdr**)malloc(sizeof(Elf32_Phdr*) * elf->programHeaderNum);
    memset(elf->programHeaders, 0, sizeof(Elf32_Phdr*) * elf->programHeaderNum);
    for (uint32_t i = 0; i < elf->programHeaderNum; i++) {
        elf->programHeaders[i] = (Elf32_Phdr*)(elf->buf + elf->fileHeader->e_phoff + elf->fileHeader->e_phentsize * i);
    }
}

void Elf_Reader_printProgramHeader(Elf32_Phdr *program);

static inline void Elf_Reader_printAllProgramHeaders(ELF_T elf)
{
    printf("Program headers:\n");
    for (uint32_t i = 0; i < elf.programHeaderNum; i++) {
        printf("\tProgram Header [%d]:\n", i);
        Elf_Reader_printProgramHeader(elf.programHeaders[i]);
    }
}

static inline void Elf_Reader_releaseElf(ELF_T *elf)
{
    free(elf->buf);
    free(elf->sectionsHeaders);
    free(elf->programHeaders);
}

ELF_T Elf_Reader_loadElf(char* fileName);

#endif
