.text
.align	2
.globl	entry
.ent	entry
entry:
.set noreorder

##
# Hardware requres this:
##
nop                          # 0x0  -- 0: reset entry
j pre_load                   # 0x4  -- 4
nop                          # 0x8  -- 8: INT ecpt entry
j interrupt_service_routine  #      -- 12
nop                          # 0x10 -- 16: other ecpt entry
j interrupt_service_routine  #      -- 20
nop                          #      -- 24

pre_load:

##
# These eight instructions must be the first instructions.
# convert.exe will correctly initialize $gp
##
lui   $gp,0x0000              #      -- 28 (+0)     .global_pointer
ori   $gp,$gp,0               #      -- 32 (+4)

#convert will set $4=.data_start in bin $5=.data_end in bin $6=.data_addr in sram
lui   $4,0                    #      -- 36 (+8)     .data_start
ori   $4,$4,0                 #      -- 40 (+12)
lui   $5,0                    #      -- 44 (+16)    .data_end
ori   $5,$5,0                 #      -- 48 (+20)
lui   $6,0                    #      -- 52 (+24)    .data_addr
ori   $6,$6,0                 #      -- 58 (+28)
b     $CHECK_DATA_SECTION     #      -- 62 (+32)
nop                           #      -- 66 (+36)

$DATA_LOADER:
lw    $3,0($4)                #      -- 70 (+40)    load data from bin
nop                           #      -- 74 (+44)
sw    $3,0($6)                #      -- 78 (+48)    store data to sram
nop                           #      -- 82 (+52)
addiu $6,$6,4                 #      -- 86 (+56)    move ptr to sram forward
addiu $4,$4,4                 #      -- 90 (+60)    move ptr to .data sram section forward

$CHECK_DATA_SECTION:
slt   $3,$4,$5                #      -- 94 (+64)
bnez  $3,$DATA_LOADER         #      -- 98 (+68)    .data exists, load it!
nop                           #      -- 102 (+72)

#convert.exe will set $4=.bss_start $5=.bss_end
lui   $4,0                    #      -- 106 (+76)   .bss_start
ori   $4,$4,0                 #      -- 110 (+80)
lui   $5,0                    #      -- 114 (+84)   .bss_end
ori   $5,$5,0                 #      -- 118 (+88)
lui   $sp,0                   #      -- 122 (+92)   .stack_pointer
ori   $sp,$sp,0xfff0          #      -- 126 (+96)   initialize stack pointer
b     $CHECK_BSS_SECTION      #      -- 130 (+100)
nop                           #      -- 134 (+104)

$BSS_CLEAR:
sw    $0,0($4)                #      -- 138 (+108)  initialize .bss sram section as 0
addiu $4,$4,4                 #      -- 142 (+112)  move ptr to .bss sram section forward

$CHECK_BSS_SECTION:
slt   $3,$4,$5                #      -- 146 (+116)
bnez  $3,$BSS_CLEAR           #      -- 150 (+120)  .bss exists, load it!
nop                           #      -- 154 (+124)

mfc0  $k0, $12
ori   $k0, 0xffff
mtc0  $k0, $12                # enable interrupts and mask
nop

jal   main                    # small os
nop

$L1:
j $L1

.set reorder
    .end    entry
