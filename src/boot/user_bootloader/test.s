	.file	1 "test.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	test
	.set	nomips16
	.set	nomicromips
	.ent	test
	.type	test, @function
test:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	li	$2,268435456			# 0x10000000
	ori	$2,$2,0x14
	sw	$2,16($fp)
	li	$2,268435456			# 0x10000000
	ori	$2,$2,0x14
	sw	$2,20($fp)
	lw	$2,20($fp)
	nop
	jalr	$2
	nop

	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	test
	.size	test, .-test
	.ident	"GCC: (GNU) 7.3.0"
