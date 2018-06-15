	.file	1 "stdio_fp.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.local	__convertBuffer
	.comm	__convertBuffer,33,4
	.local	__printfBuffer
	.comm	__printfBuffer,128,4
	.align	2
	.globl	putchar
	.set	nomips16
	.set	nomicromips
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
$L2:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x1
	lw	$2,0($2)
	nop
	bne	$2,$0,$L2
	nop

	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x2
	lb	$3,8($fp)
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
	.set	nomips16
	.set	nomicromips
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
	b	$L4
	nop

$L6:
	lw	$2,24($fp)
	nop
	lb	$3,0($2)
	li	$2,10			# 0xa
	bne	$3,$2,$L5
	nop

	li	$4,13			# 0xd
	jal	putchar
	nop

$L5:
	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	lb	$2,0($2)
	nop
	move	$4,$2
	jal	putchar
	nop

$L4:
	lw	$2,24($fp)
	nop
	lb	$2,0($2)
	nop
	bne	$2,$0,$L6
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
	.align	2
	.globl	getchar
	.set	nomips16
	.set	nomicromips
	.ent	getchar
	.type	getchar, @function
getchar:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	nop
$L8:
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x5
	lw	$2,0($2)
	nop
	beq	$2,$0,$L8
	nop

	li	$2,528482304			# 0x1f800000
	lw	$2,0($2)
	nop
	sll	$2,$2,24
	sra	$2,$2,24
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	getchar
	.size	getchar, .-getchar
	.align	2
	.globl	getnum
	.set	nomips16
	.set	nomicromips
	.ent	getnum
	.type	getnum, @function
getnum:
	.frame	$fp,40,$31		# vars= 8, regs= 4/0, args= 16, gp= 0
	.mask	0xc0030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	move	$fp,$sp
	move	$17,$0
	sw	$0,20($fp)
	move	$16,$0
	b	$L11
	nop

$L17:
	jal	getchar
	nop

	sb	$2,16($fp)
	lbu	$3,16($fp)
	li	$2,10			# 0xa
	beq	$3,$2,$L12
	nop

	lbu	$3,16($fp)
	li	$2,13			# 0xd
	beq	$3,$2,$L12
	nop

	lbu	$3,16($fp)
	li	$2,32			# 0x20
	beq	$3,$2,$L12
	nop

	lbu	$2,16($fp)
	nop
	sltu	$2,$2,48
	bne	$2,$0,$L13
	nop

	lbu	$2,16($fp)
	nop
	sltu	$2,$2,58
	beq	$2,$0,$L13
	nop

	lbu	$2,16($fp)
	nop
	addiu	$2,$2,-48
	sb	$2,16($fp)
	b	$L14
	nop

$L13:
	lbu	$3,16($fp)
	li	$2,8			# 0x8
	bne	$3,$2,$L15
	nop

	blez	$16,$L16
	nop

	addiu	$16,$16,-1
$L16:
	li	$2,10			# 0xa
	div	$0,$17,$2
	bne	$2,$0,1f
	nop
	break	7
1:
	mfhi	$2
	mflo	$17
	b	$L11
	nop

$L15:
	lbu	$3,16($fp)
	li	$2,45			# 0x2d
	bne	$3,$2,$L14
	nop

	bne	$16,$0,$L14
	nop

	li	$2,1			# 0x1
	sw	$2,20($fp)
	b	$L11
	nop

$L14:
	move	$2,$17
	sll	$2,$2,2
	addu	$2,$2,$17
	sll	$2,$2,1
	move	$3,$2
	lbu	$2,16($fp)
	nop
	addu	$17,$3,$2
	addiu	$16,$16,1
$L11:
	slt	$2,$16,10
	bne	$2,$0,$L17
	nop

$L12:
	lw	$2,20($fp)
	nop
	beq	$2,$0,$L18
	nop

	subu	$17,$0,$17
$L18:
	move	$2,$17
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	getnum
	.size	getnum, .-getnum
	.align	2
	.globl	getHexNum
	.set	nomips16
	.set	nomicromips
	.ent	getHexNum
	.type	getHexNum, @function
getHexNum:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$0,24($fp)
	sw	$0,16($fp)
	b	$L21
	nop

$L29:
	jal	getchar
	nop

	sb	$2,20($fp)
	lbu	$3,20($fp)
	li	$2,13			# 0xd
	beq	$3,$2,$L31
	nop

	lbu	$3,20($fp)
	li	$2,10			# 0xa
	beq	$3,$2,$L23
	nop

	lbu	$3,20($fp)
	li	$2,13			# 0xd
	beq	$3,$2,$L23
	nop

	lbu	$3,20($fp)
	li	$2,32			# 0x20
	beq	$3,$2,$L23
	nop

	lbu	$2,20($fp)
	nop
	sltu	$2,$2,48
	bne	$2,$0,$L24
	nop

	lbu	$2,20($fp)
	nop
	sltu	$2,$2,58
	beq	$2,$0,$L24
	nop

	lbu	$2,20($fp)
	nop
	addiu	$2,$2,-48
	sb	$2,20($fp)
	b	$L25
	nop

$L24:
	lbu	$2,20($fp)
	nop
	sltu	$2,$2,65
	bne	$2,$0,$L26
	nop

	lbu	$2,20($fp)
	nop
	sltu	$2,$2,91
	beq	$2,$0,$L26
	nop

	lbu	$2,20($fp)
	nop
	addiu	$2,$2,-55
	sb	$2,20($fp)
	b	$L25
	nop

$L26:
	lbu	$2,20($fp)
	nop
	sltu	$2,$2,97
	bne	$2,$0,$L27
	nop

	lbu	$2,20($fp)
	nop
	sltu	$2,$2,123
	beq	$2,$0,$L27
	nop

	lbu	$2,20($fp)
	nop
	addiu	$2,$2,-87
	sb	$2,20($fp)
	b	$L25
	nop

$L27:
	lbu	$3,20($fp)
	li	$2,8			# 0x8
	bne	$3,$2,$L25
	nop

	lw	$2,16($fp)
	nop
	blez	$2,$L28
	nop

	lw	$2,16($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,16($fp)
$L28:
	lw	$2,24($fp)
	nop
	srl	$2,$2,4
	sw	$2,24($fp)
	b	$L21
	nop

$L25:
	lw	$2,24($fp)
	nop
	sll	$3,$2,4
	lbu	$2,20($fp)
	nop
	addu	$2,$3,$2
	sw	$2,24($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L21:
	lw	$2,16($fp)
	nop
	slt	$2,$2,16
	bne	$2,$0,$L29
	nop

	b	$L23
	nop

$L31:
	nop
$L23:
	lw	$2,24($fp)
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	getHexNum
	.size	getHexNum, .-getHexNum
	.rdata
	.align	2
$LC0:
	.ascii	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\000"
	.text
	.align	2
	.globl	itoa
	.set	nomips16
	.set	nomicromips
	.ent	itoa
	.type	itoa, @function
itoa:
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	lui	$2,%hi(__convertBuffer)
	addiu	$2,$2,%lo(__convertBuffer)
	sw	$2,0($fp)
	lui	$2,%hi(__convertBuffer)
	addiu	$2,$2,%lo(__convertBuffer)
	sw	$2,4($fp)
	lw	$2,24($fp)
	nop
	bgez	$2,$L34
	nop

	lw	$3,28($fp)
	li	$2,10			# 0xa
	bne	$3,$2,$L34
	nop

	lw	$2,4($fp)
	nop
	addiu	$3,$2,1
	sw	$3,4($fp)
	li	$3,45			# 0x2d
	sb	$3,0($2)
	lw	$2,0($fp)
	nop
	addiu	$2,$2,1
	sw	$2,0($fp)
	lw	$2,24($fp)
	nop
	subu	$2,$0,$2
	sw	$2,24($fp)
$L34:
	lw	$3,24($fp)
	lw	$2,28($fp)
	nop
	divu	$0,$3,$2
	bne	$2,$0,1f
	nop
	break	7
1:
	mfhi	$2
	move	$4,$2
	lw	$2,4($fp)
	nop
	addiu	$3,$2,1
	sw	$3,4($fp)
	lui	$3,%hi($LC0)
	addiu	$3,$3,%lo($LC0)
	addu	$3,$4,$3
	lb	$3,0($3)
	nop
	sb	$3,0($2)
	lw	$3,24($fp)
	lw	$2,28($fp)
	nop
	divu	$0,$3,$2
	bne	$2,$0,1f
	nop
	break	7
1:
	mfhi	$2
	mflo	$2
	sw	$2,24($fp)
	lw	$2,24($fp)
	nop
	bne	$2,$0,$L34
	nop

	lw	$2,4($fp)
	nop
	addiu	$3,$2,-1
	sw	$3,4($fp)
	sb	$0,0($2)
	b	$L35
	nop

$L36:
	lw	$2,0($fp)
	nop
	lbu	$2,0($2)
	nop
	sb	$2,8($fp)
	lw	$2,4($fp)
	nop
	lb	$3,0($2)
	lw	$2,0($fp)
	nop
	sb	$3,0($2)
	lw	$2,4($fp)
	lbu	$3,8($fp)
	nop
	sb	$3,0($2)
	lw	$2,0($fp)
	nop
	addiu	$2,$2,1
	sw	$2,0($fp)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,4($fp)
$L35:
	lw	$3,4($fp)
	lw	$2,0($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L36
	nop

	lui	$2,%hi(__convertBuffer)
	addiu	$2,$2,%lo(__convertBuffer)
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	itoa
	.size	itoa, .-itoa
	.align	2
	.globl	_memset
	.set	nomips16
	.set	nomicromips
	.ent	_memset
	.type	_memset, @function
_memset:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	sw	$5,12($fp)
	move	$2,$6
	sb	$2,16($fp)
	b	$L39
	nop

$L40:
	lw	$2,8($fp)
	nop
	addiu	$3,$2,1
	sw	$3,8($fp)
	lbu	$3,16($fp)
	nop
	sb	$3,0($2)
	lw	$2,12($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,12($fp)
$L39:
	lw	$2,12($fp)
	nop
	bne	$2,$0,$L40
	nop

	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_memset
	.size	_memset, .-_memset
	.align	2
	.globl	_strcat
	.set	nomips16
	.set	nomicromips
	.ent	_strcat
	.type	_strcat, @function
_strcat:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	lw	$2,16($fp)
	nop
	sw	$2,0($fp)
	b	$L42
	nop

$L43:
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L42:
	lw	$2,16($fp)
	nop
	lb	$2,0($2)
	nop
	bne	$2,$0,$L43
	nop

	b	$L44
	nop

$L45:
	lw	$3,20($fp)
	nop
	addiu	$2,$3,1
	sw	$2,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$4,$2,1
	sw	$4,16($fp)
	lb	$3,0($3)
	nop
	sb	$3,0($2)
$L44:
	lw	$2,16($fp)
	nop
	lb	$2,0($2)
	nop
	bne	$2,$0,$L45
	nop

	lw	$2,0($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_strcat
	.size	_strcat, .-_strcat
	.align	2
	.globl	_strlen
	.set	nomips16
	.set	nomicromips
	.ent	_strlen
	.type	_strlen, @function
_strlen:
	.frame	$fp,16,$31		# vars= 0, regs= 3/0, args= 0, gp= 0
	.mask	0x40030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	sw	$17,8($sp)
	sw	$16,4($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	move	$17,$0
	lw	$16,16($fp)
	b	$L48
	nop

$L49:
	addiu	$17,$17,1
	addiu	$16,$16,1
$L48:
	lb	$2,0($16)
	nop
	bne	$2,$0,$L49
	nop

	move	$2,$17
	move	$sp,$fp
	lw	$fp,12($sp)
	lw	$17,8($sp)
	lw	$16,4($sp)
	addiu	$sp,$sp,16
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_strlen
	.size	_strlen, .-_strlen
	.align	2
	.globl	printf
	.set	nomips16
	.set	nomicromips
	.ent	printf
	.type	printf, @function
printf:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)						# save $4 to memory: format
	sw	$5,36($fp)						# save $5 to memory
	sw	$6,40($fp)						# save $6 to memory
	sw	$7,44($fp)						# save $7 to memory
	addiu	$2,$fp,36
	sw	$2,16($fp)
	lw	$2,32($fp)
	lw	$6,16($fp)
	move	$5,$2						# load format (unsigned char*) to $5
	lui	$2,%hi(__printfBuffer)
	addiu	$4,$2,%lo(__printfBuffer)	# load __printfBuffer (unsigned char*) to $4
	jal	_printf							# other parameters are in the memory
	nop

	sw	$0,16($fp)
	lui	$2,%hi(__printfBuffer)
	addiu	$4,$2,%lo(__printfBuffer)
	jal	puts
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
	.end	printf
	.size	printf, .-printf
	.align	2
	.globl	sprintf
	.set	nomips16
	.set	nomicromips
	.ent	sprintf
	.type	sprintf, @function
sprintf:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$6,40($fp)
	sw	$7,44($fp)
	addiu	$2,$fp,36
	addiu	$2,$2,4
	sw	$2,16($fp)
	lw	$2,36($fp)
	lw	$6,16($fp)
	move	$5,$2
	lw	$4,32($fp)
	jal	_printf
	nop

	sw	$0,16($fp)
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	sprintf
	.size	sprintf, .-sprintf
	.rdata
	.align	2
$LC1:
	.ascii	".\000"
	.text
	.align	2
	.globl	ftoa
	.set	nomips16
	.set	nomicromips
	.ent	ftoa
	.type	ftoa, @function
ftoa:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	swc1	$f12,32($fp)
	lwc1	$f0,32($fp)
	nop
	.set	macro
	trunc.w.s $f0,$f0,$2
	.set	nomacro
	mfc1	$2,$f0
	li	$5,10			# 0xa
	move	$4,$2
	jal	itoa
	nop

	lui	$2,%hi($LC1)
	addiu	$5,$2,%lo($LC1)
	lui	$2,%hi(__convertBuffer)
	addiu	$4,$2,%lo(__convertBuffer)
	jal	_strcat
	nop

	lwc1	$f12,32($fp)
	jal	FP_Abs
	nop

	swc1	$f0,32($fp)
	lwc1	$f0,32($fp)
	nop
	.set	macro
	trunc.w.s $f0,$f0,$2
	.set	nomacro
	cvt.s.w	$f0,$f0
	lwc1	$f2,32($fp)
	nop
	sub.s	$f2,$f2,$f0
	lui	$2,%hi($LC2)
	lwc1	$f0,%lo($LC2)($2)
	nop
	mul.s	$f0,$f2,$f0
	.set	macro
	trunc.w.s $f0,$f0,$2
	.set	nomacro
	mfc1	$2,$f0
	nop
	sw	$2,16($fp)
	li	$5,10			# 0xa
	lw	$4,16($fp)
	jal	itoa
	nop

	addiu	$2,$fp,20
	move	$5,$2
	lui	$2,%hi(__convertBuffer)
	addiu	$4,$2,%lo(__convertBuffer)
	jal	_strcat
	nop

	lui	$2,%hi(__convertBuffer)
	addiu	$2,$2,%lo(__convertBuffer)
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	ftoa
	.size	ftoa, .-ftoa
	.align	2
	.globl	_printf
	.set	nomips16
	.set	nomicromips
	.ent	_printf
	.type	_printf, @function
_printf:
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
	sw	$5,28($fp)
	sw	$6,32($fp)
	move	$6,$0
	li	$5,128			# 0x80
	lw	$4,24($fp)
	jal	_memset
	nop

	b	$L56
	nop

$L66:
	lw	$2,28($fp)
	nop
	lb	$3,0($2)
	li	$2,37			# 0x25
	beq	$3,$2,$L57
	nop

	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,28($fp)
	nop
	lb	$3,0($3)
	nop
	sb	$3,0($2)
	b	$L58
	nop

$L57:
	lw	$2,28($fp)
	nop
	addiu	$2,$2,1
	sw	$2,28($fp)
	lw	$2,28($fp)
	nop
	lb	$2,0($2)
	nop
	addiu	$2,$2,-88
	sltu	$3,$2,33
	beq	$3,$0,$L59
	nop

	sll	$3,$2,2
	lui	$2,%hi($L61)
	addiu	$2,$2,%lo($L61)
	addu	$2,$3,$2
	lw	$2,0($2)
	nop
	jr	$2
	nop

	.rdata
	.align	2
	.align	2
$L61:
	.word	$L60
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L62
	.word	$L63
	.word	$L59
	.word	$L64
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L65
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L59
	.word	$L60
	.text
$L63:
	lw	$2,32($fp)
	nop
	lw	$2,0($2)
	li	$5,10			# 0xa
	move	$4,$2
	jal	itoa
	nop

	lui	$2,%hi(__convertBuffer)
	addiu	$5,$2,%lo(__convertBuffer)
	lw	$4,24($fp)
	jal	_strcat
	nop

	lw	$4,24($fp)
	jal	_strlen
	nop

	move	$3,$2
	lw	$2,24($fp)
	nop
	addu	$2,$2,$3
	sw	$2,24($fp)
	lw	$2,32($fp)
	nop
	addiu	$2,$2,4
	sw	$2,32($fp)
	b	$L58
	nop

$L60:
	lw	$2,32($fp)
	nop
	lw	$2,0($2)
	li	$5,16			# 0x10
	move	$4,$2
	jal	itoa
	nop

	lw	$4,24($fp)
	jal	_strlen
	nop

	move	$3,$2
	lw	$2,24($fp)
	nop
	addu	$2,$2,$3
	sw	$2,24($fp)
	lw	$2,32($fp)
	nop
	addiu	$2,$2,4
	sw	$2,32($fp)
	b	$L58
	nop

$L62:
	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,32($fp)
	nop
	lb	$3,0($3)
	nop
	sb	$3,0($2)
	lw	$2,32($fp)
	nop
	addiu	$2,$2,4
	sw	$2,32($fp)
	b	$L58
	nop

$L64:
	lw	$2,32($fp)
	nop
	lwc1	$f0,0($2)
	nop
	mov.s	$f12,$f0
	jal	ftoa
	nop

	lw	$4,24($fp)
	jal	_strlen
	nop

	move	$3,$2
	lw	$2,24($fp)
	nop
	addu	$2,$2,$3
	sw	$2,24($fp)
	b	$L58
	nop

$L65:
	lw	$2,32($fp)
	nop
	lw	$2,0($2)
	nop
	move	$5,$2
	lw	$4,24($fp)
	jal	_strcat
	nop

	lw	$4,24($fp)
	jal	_strlen
	nop

	move	$3,$2
	lw	$2,24($fp)
	nop
	addu	$2,$2,$3
	sw	$2,24($fp)
	lw	$2,32($fp)
	nop
	addiu	$2,$2,4
	sw	$2,32($fp)
	b	$L58
	nop

$L59:
	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	li	$3,37			# 0x25
	sb	$3,0($2)
	lw	$2,24($fp)
	nop
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,28($fp)
	nop
	lb	$3,0($3)
	nop
	sb	$3,0($2)
	nop
$L58:
	lw	$2,28($fp)
	nop
	addiu	$2,$2,1
	sw	$2,28($fp)
$L56:
	lw	$2,28($fp)
	nop
	lb	$2,0($2)
	nop
	bne	$2,$0,$L66
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
	.end	_printf
	.size	_printf, .-_printf
	.rdata
	.align	2
$LC2:
	.word	1232348160
	.ident	"GCC: (GNU) 7.3.0"
