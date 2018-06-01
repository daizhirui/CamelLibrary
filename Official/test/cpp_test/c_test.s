	.file	1 "c_test.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	user_interrupt
	.ent	user_interrupt
	.type	user_interrupt, @function
user_interrupt:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	reorder
	.end	user_interrupt
	.size	user_interrupt, .-user_interrupt
	.align	2
	.globl	putchar
	.ent	putchar
	.type	putchar, @function
putchar:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	move	$2,$4
	sb	$2,8($fp)
	nop
$L3:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x1
	lw	$2,0($2)
	nop
	bne	$2,$0,$L3
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x2
	lbu	$3,8($fp)
	nop
	sw	$3,0($2)
	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	putchar
	.size	putchar, .-putchar
	.align	2
	.globl	puts
	.ent	puts
	.type	puts, @function
puts:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	b	$L5
	nop

$L7:
	lw	$2,24($fp)
	nop
	lb	$3,0($2)
	li	$2,10			# 0xa
	bne	$3,$2,$L6
	nop

	li	$4,13			# 0xd
	jal	putchar
	nop

$L6:
	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	lb	$2,0($2)
	nop
	andi	$2,$2,0x00ff
	move	$4,$2
	jal	putchar
	nop

$L5:
	lw	$2,24($fp)
	nop
	lb	$2,0($2)
	nop
	bne	$2,$0,$L7
	nop

	nop
	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	puts
	.size	puts, .-puts
	.rdata
	.align	2
$LC0:
	.ascii	"Hello!\000"
	.text
	.align	2
	.globl	main


	.ent	main
	.type	main, @function
main:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
$L9:
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	jal	puts
	nop

	b	$L9
	nop

	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 7.3.0"
