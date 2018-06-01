    .text
        .align  2
        .globl user_interrupt
        .set	nomips16
    	.set	nomicromips
        .ent    user_interrupt
        .type	user_interrupt, @function
user_interrupt:
    .set	noreorder
    .set    noat
    .set	nomacro
    nop
    jr  $31
    nop
        .set	macro
        .set	reorder
        .end	user_interrupt
        .size	user_interrupt, .-user_interrupt

        .align  2
        .globl main
        .set	nomips16
    	.set	nomicromips
        .ent main
main:
        .set    noreorder
        .set    noat
        .set	nomacro

    li      $1, 0x1f800000  #uart_port
    ori      $4, $0, 'h'
puts:
    lw      $5, 1($1)       #check busy
    bgtz     $5, puts
    nop
    sb      $4, 2($3)       #write
    b       puts
    nop

        .set	macro
    	.set	reorder
    	.end	main
    	.size	main, .-main
    	.ident	"GCC: (GNU) 7.3.0"
