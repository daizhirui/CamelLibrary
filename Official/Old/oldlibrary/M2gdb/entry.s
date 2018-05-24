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
   lui   $gp,0x0000              #      -- 28
   ori   $gp,$gp,0
   #convert.exe will set $4=.sbss_start $5=.bss_end
   lui   $4,0
   ori   $4,$4,0
   lui   $5,0
   ori   $5,$5,0
   lui   $sp,0
   ori   $sp,$sp,0xfff0     #initialize stack pointer
$BSS_CLEAR:
   sw    $0,0($4)
   slt   $3,$4,$5
   bnez  $3,$BSS_CLEAR
   addiu $4,$4,4

   mfc0  $k0, $12
   ori   $k0, 0xffff
   mtc0  $k0, $12        # enable interrupts and mask
   nop

   jal   main           # small os
   nop

$L1:
   j $L1

  .set reorder
        .end    entry

