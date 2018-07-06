

###################################################
   .global OS_AsmGetCauseReg
   .ent OS_AsmGetCauseReg
OS_AsmGetCauseReg:
   .set noreorder
   mfc0  $2, $13
   jr    $31
   nop
   nop

   .set reorder
   .end OS_AsmGetCauseReg



###################################################
   .global OS_AsmGetRandomReg
   .ent OS_AsmGetRandomReg
OS_AsmGetRandomReg:
   .set noreorder
   mfc0  $2, $3
   jr    $31
   nop
   nop

   .set reorder
   .end OS_AsmGetRandomReg

###################################################
   #address 0x???
   # prog main: sw wd 0x100xxxxx
   # prog nvr : sw wd 0x102xxxxx
   #
   .global OS_EfWrite
   .ent OS_EfWrite
OS_EfWrite:
   .set noreorder
   nop
   sw   $4, 0($5)       # sw $4=word $5=address  
   nop 
   li   $5,0x7          # test ef status  0: no busy  1: busy
   li   $4,0x10100000   # ef status read
   nop                  # delay slot
efw_wait_:
   lw   $2,0($4)        # ef status word load
   and  $2, $2, $5      # must be all 0
   bgtz $2, efw_wait_   # ef status 1 = busy
   nop
   j    $31             # return if status=0
   nop
   nop

   .set reorder
   .end OS_EfWrite

###################################################
   #address 0x???
   #
   # sector erase    sw y 0x101xxxxx
   # chip   erase    sw y 0x103xxxxx
   #
   .global OS_EfErase
   .ent OS_EfErase
OS_EfErase:
   .set noreorder
   nop
   sw   $0, 0($4)       # sw $4=address
   nop
   li   $5,0x7          # test ef status  0: no busy  1: busy
   li   $4,0x10100000   # ef status read
   nop                  # delay slot
efe_wait_:
   lw   $2,0($4)        # ef status word load
   and  $2, $2, $5      # must be all 0
   bgtz $2, efe_wait_   # ef status 1 = busy
   nop
   j    $31             # return if status=0
   nop
   nop

   .set reorder
   .end OS_EfErase

