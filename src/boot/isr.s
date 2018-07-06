   #address 0x3c
###################################################
   #address 0x3c
   .global interrupt_service_routine
   .ent interrupt_service_routine
interrupt_service_routine:
   .set noreorder
   .set noat

   #Registers $26 and $27 are reserved for the OS: $k0 and $k1
   #Save all temporary registers
   #Slots 0($29) through 12($29) reserved for saving a0-a3
   addi  $29, $29, -108  #adjust sp
   sw    $1,  16($29)    #at
   sw    $2,  20($29)    #v0
   sw    $3,  24($29)    #v1
   sw    $4,  28($29)    #a0
   sw    $5,  32($29)    #a1
   sw    $6,  36($29)    #a2
   sw    $7,  40($29)    #a3
   sw    $8,  44($29)    #t0
   sw    $9,  48($29)    #t1
   sw    $10, 52($29)    #t2
   sw    $11, 56($29)    #t3
   sw    $12, 60($29)    #t4
   sw    $13, 64($29)    #t5
   sw    $14, 68($29)    #t6
   sw    $15, 72($29)    #t7
   sw    $24, 76($29)    #t8
   sw    $25, 80($29)    #t9
   sw    $31, 84($29)    #ra (return address)
   mfc0  $26, $14        #C0_EPC=14 (Exception Program Counter: the address of where to restart after exception)
   sub   $26, $26, 0x4   #Skip the address of the instruction which results in this exception
   sw    $26, 88($29)    #store C0_EPC
   li    $s0, 0x01001ff8 #0x01001ff8 is an address in the sram for debug usage
   sw    $26, ($s0)      #save pc to PC_LOC for debug continue option use
   mfhi  $27
   sw    $27, 92($29)    #hi
   mflo  $27
   sw    $27, 96($29)    #lo
   sw    $30, 100($29)   #fp
   li    $8, 0x01001ff4  #0x01001ff4 is an address in the sram to store the current interrupt depth(INT_COUNT)
   lw    $9, ($8)        #load the current interrupt depth
   addi  $9, $9, 1       #increase the interrupt depth
   sw    $9, ($8)        #update the interrupt count in the sram
   sll   $9, $9, 2       #($9=$9*4)calculate the distance from the address for storing $sp to the address of INT_COUNT
   sub   $8, $8, $9      #this is the location to store $sp
   sw    $29, ($8)       #save $sp to the location near INT_COUNT
   li    $2, 0x1001ffc   #0x01001ffc is an address in the sram for recording if the interrupt is from the user.
   li    $3, 0x1
   sw    $3, 0($2)       #set USER_INT as true(1)
   jal   user_interrupt  #jump to user's interrupt function
   nop
   addi  $5,  $29, 0     #load the current $sp to $5
   li    $8, 0x01001ff4  #0x01001ff4 is an address in the sram to store the current interrupt depth
   lw    $9, ($8)        #load the current interrupt depth
   sub   $9, $9, 1       #decrease the interrupt depth
   sw    $9, ($8)        #update the interrupt count

   #Restore all temporary registers
   lw    $1,  16($29)    #at
   lw    $2,  20($29)    #v0
   lw    $3,  24($29)    #v1
   lw    $4,  28($29)    #a0
   lw    $5,  32($29)    #a1
   lw    $6,  36($29)    #a2
   lw    $7,  40($29)    #a3
   lw    $8,  44($29)    #t0
   lw    $9,  48($29)    #t1
   lw    $10, 52($29)    #t2
   lw    $11, 56($29)    #t3
   lw    $12, 60($29)    #t4
   lw    $13, 64($29)    #t5
   lw    $14, 68($29)    #t6
   lw    $15, 72($29)    #t7
   lw    $24, 76($29)    #t8
   lw    $25, 80($29)    #t9
   lw    $31, 84($29)    #ra
   lw    $26, 88($29)    #pc
   lw    $27, 92($29)    #hi
   mthi  $27
   lw    $27, 96($29)    #lo
   mtlo  $27
   lw    $30, 100($29)   #fp
   addi  $29, $29, 108   #adjust sp

   #check if the interrupt is from user or not
   #this part doesn't do any work now!
   li    $s0, 0x01001ffc #0x01001ffc is an address in the sram for recording if the interrupt is from the user.
   lw    $s1, ($s0)
   addi  $s1, $s1, -1
   #beqz  $s1, goto_user_isr

   jr    $26
   rfe                    # this is important, restore STATUS
   nop

goto_user_isr:
   li    $s0, 0x1001ffc
   sw    $0, ($s0)  #reset USER_INT
   j     0x10000008
   nop

   .set reorder
   .set at

   .end interrupt_service_routine

   #normally clear the interrupt source here
