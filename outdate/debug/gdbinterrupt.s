	.file	1 "gdbinterrupt.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.rdata
	.align	2
$LC0:
	.ascii	"\015UART SYNC DONE!\015\000"
	.text
	.align	2
	.globl	_Uart_sync
	.set	nomips16
	.set	nomicromips
	.ent	_Uart_sync
	.type	_Uart_sync, @function
_Uart_sync:
	.frame	$fp,88,$31		# vars= 64, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$fp,80($sp)
	move	$fp,$sp
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x702
	lw	$2,0($2)
	nop
	sw	$2,32($fp)
	lw	$3,32($fp)
	li	$2,-113			# 0xffffffffffffff8f
	and	$2,$3,$2
	sw	$2,32($fp)
	li	$2,6			# 0x6
	sw	$2,48($fp)
	li	$2,5			# 0x5
	sw	$2,52($fp)
	li	$2,4			# 0x4
	sw	$2,56($fp)
	li	$2,2			# 0x2
	sw	$2,60($fp)
	li	$2,7			# 0x7
	sw	$2,64($fp)
	li	$2,1			# 0x1
	sw	$2,68($fp)
	sw	$0,72($fp)
	li	$2,3			# 0x3
	sw	$2,76($fp)
	sw	$0,16($fp)
	b	$L2
	nop

$L3:
	lw	$2,16($fp)
	nop
	sll	$2,$2,2
	addiu	$3,$fp,16
	addu	$2,$3,$2
	lw	$2,32($2)
	nop
	sll	$2,$2,4
	lw	$3,32($fp)
	nop
	or	$2,$3,$2
	sw	$2,36($fp)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x702
	lw	$3,36($fp)
	nop
	sw	$3,0($2)
	jal	getch
	nop

	sll	$3,$2,24
	sra	$3,$3,24
	lw	$2,16($fp)
	addiu	$4,$fp,16
	addu	$2,$4,$2
	sb	$3,24($2)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L2:
	lw	$2,16($fp)
	nop
	slt	$2,$2,8
	bne	$2,$0,$L3
	nop

	li	$2,-1			# 0xffffffffffffffff
	sw	$2,24($fp)
	sw	$0,28($fp)
	sw	$0,20($fp)
	sw	$0,16($fp)
	b	$L4
	nop

$L8:
	lw	$2,24($fp)
	nop
	bgez	$2,$L5
	nop

	lw	$2,16($fp)
	addiu	$3,$fp,16
	addu	$2,$3,$2
	lb	$3,24($2)
	li	$2,1			# 0x1
	bne	$3,$2,$L5
	nop

	lw	$2,16($fp)
	nop
	sw	$2,24($fp)
	b	$L6
	nop

$L5:
	lw	$2,24($fp)
	nop
	bltz	$2,$L6
	nop

	lw	$2,16($fp)
	addiu	$3,$fp,16
	addu	$2,$3,$2
	lb	$3,24($2)
	li	$2,1			# 0x1
	beq	$3,$2,$L6
	nop

	lw	$3,16($fp)
	lw	$2,24($fp)
	nop
	subu	$2,$3,$2
	lw	$3,28($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L7
	nop

	lw	$3,16($fp)
	lw	$2,24($fp)
	nop
	subu	$2,$3,$2
	sw	$2,28($fp)
	lw	$2,24($fp)
	nop
	sw	$2,20($fp)
$L7:
	li	$2,-1			# 0xffffffffffffffff
	sw	$2,24($fp)
$L6:
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L4:
	lw	$2,16($fp)
	nop
	slt	$2,$2,8
	bne	$2,$0,$L8
	nop

	lw	$2,28($fp)
	nop
	bne	$2,$0,$L9
	nop

	li	$2,8			# 0x8
	sw	$2,28($fp)
$L9:
	lw	$2,28($fp)
	nop
	srl	$3,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	move	$3,$2
	lw	$2,20($fp)
	nop
	addu	$2,$2,$3
	sw	$2,20($fp)
	lw	$2,20($fp)
	nop
	sll	$2,$2,2
	addiu	$3,$fp,16
	addu	$2,$3,$2
	lw	$2,32($2)
	nop
	sll	$2,$2,4
	lw	$3,32($fp)
	nop
	or	$2,$3,$2
	sw	$2,36($fp)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x702
	lw	$3,36($fp)
	nop
	sw	$3,0($2)
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	jal	puts
	nop

	nop
	move	$sp,$fp
	lw	$31,84($sp)
	lw	$fp,80($sp)
	addiu	$sp,$sp,88
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_Uart_sync
	.size	_Uart_sync, .-_Uart_sync
	.align	2
	.globl	sys_init
	.set	nomips16
	.set	nomicromips
	.ent	sys_init
	.type	sys_init, @function
sys_init:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x502
	li	$3,255			# 0xff
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x503
	li	$3,255			# 0xff
	sw	$3,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x500
	sw	$0,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x704
	sw	$0,0($2)
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0xc00
	sw	$0,0($2)
	li	$2,16777216			# 0x1000000
	ori	$2,$2,0x1ff4
	sw	$0,0($2)
	li	$2,16777216			# 0x1000000
	ori	$2,$2,0x1ffc
	sw	$0,0($2)
	nop
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	sys_init
	.size	sys_init, .-sys_init
	.align	2
	.globl	_w_func
	.set	nomips16
	.set	nomicromips
	.ent	_w_func
	.type	_w_func, @function
_w_func:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,20($fp)
	jal	getnum
	nop

	sw	$2,24($fp)
	sw	$0,16($fp)
	b	$L12
	nop

$L13:
	jal	getnum
	nop

	sw	$2,28($fp)
	lw	$2,20($fp)
	lw	$3,28($fp)
	nop
	sw	$3,0($2)
	lw	$2,20($fp)
	nop
	addiu	$2,$2,4
	sw	$2,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L12:
	lw	$2,16($fp)
	lw	$3,24($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L13
	nop

	li	$4,6			# 0x6
	jal	putc_uart
	nop

	nop
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_w_func
	.size	_w_func, .-_w_func
	.rdata
	.align	2
$LC1:
	.ascii	" \000"
	.text
	.align	2
	.globl	_r_func
	.set	nomips16
	.set	nomicromips
	.ent	_r_func
	.type	_r_func, @function
_r_func:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,20($fp)
	jal	getnum
	nop

	sw	$2,24($fp)
	li	$4,2			# 0x2
	jal	putc_uart
	nop

	sw	$0,16($fp)
	b	$L15
	nop

$L16:
	lw	$2,20($fp)
	nop
	lw	$2,0($2)
	nop
	sw	$2,28($fp)
	lw	$4,28($fp)
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	lw	$2,20($fp)
	nop
	addiu	$2,$2,4
	sw	$2,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L15:
	lw	$2,16($fp)
	lw	$3,24($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L16
	nop

	li	$4,3			# 0x3
	jal	putc_uart
	nop

	nop
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_r_func
	.size	_r_func, .-_r_func
	.align	2
	.globl	_R_func
	.set	nomips16
	.set	nomicromips
	.ent	_R_func
	.type	_R_func, @function
_R_func:
	.frame	$fp,440,$31		# vars= 416, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-440
	sw	$31,436($sp)
	sw	$fp,432($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,20($fp)
	sw	$0,16($fp)
	b	$L18
	nop

$L19:
	jal	getnum
	nop

	move	$4,$2
	lw	$2,16($fp)
	nop
	sll	$2,$2,2
	addiu	$3,$fp,16
	addu	$2,$3,$2
	sw	$4,12($2)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L18:
	lw	$2,16($fp)
	lw	$3,20($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L19
	nop

	li	$4,2			# 0x2
	jal	putc_uart
	nop

	sw	$0,16($fp)
	b	$L20
	nop

$L21:
	lw	$2,16($fp)
	nop
	sll	$2,$2,2
	addiu	$3,$fp,16
	addu	$2,$3,$2
	lw	$2,12($2)
	nop
	lw	$2,0($2)
	nop
	sw	$2,24($fp)
	lw	$4,24($fp)
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L20:
	lw	$2,16($fp)
	lw	$3,20($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L21
	nop

	li	$4,3			# 0x3
	jal	putc_uart
	nop

	nop
	move	$sp,$fp
	lw	$31,436($sp)
	lw	$fp,432($sp)
	addiu	$sp,$sp,440
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_R_func
	.size	_R_func, .-_R_func
	.align	2
	.globl	_s_func
	.set	nomips16
	.set	nomicromips
	.ent	_s_func
	.type	_s_func, @function
_s_func:
	.frame	$fp,48,$31		# vars= 24, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,20($fp)
	jal	getnum
	nop

	sw	$2,24($fp)
	jal	getnum
	nop

	sw	$2,28($fp)
	lw	$2,20($fp)
	nop
	lw	$2,0($2)
	lw	$3,24($fp)
	nop
	addu	$2,$3,$2
	sw	$2,20($fp)
	sw	$0,16($fp)
	b	$L23
	nop

$L24:
	jal	getnum
	nop

	sw	$2,32($fp)
	lw	$2,20($fp)
	lw	$3,32($fp)
	nop
	sw	$3,0($2)
	lw	$2,20($fp)
	nop
	addiu	$2,$2,4
	sw	$2,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L23:
	lw	$2,16($fp)
	lw	$3,28($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L24
	nop

	li	$4,6			# 0x6
	jal	putc_uart
	nop

	nop
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_s_func
	.size	_s_func, .-_s_func
	.align	2
	.globl	_l_func
	.set	nomips16
	.set	nomicromips
	.ent	_l_func
	.type	_l_func, @function
_l_func:
	.frame	$fp,48,$31		# vars= 24, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,20($fp)
	jal	getnum
	nop

	sw	$2,24($fp)
	jal	getnum
	nop

	sw	$2,28($fp)
	lw	$2,20($fp)
	nop
	lw	$2,0($2)
	lw	$3,24($fp)
	nop
	addu	$2,$3,$2
	sw	$2,20($fp)
	li	$4,2			# 0x2
	jal	putc_uart
	nop

	sw	$0,16($fp)
	b	$L26
	nop

$L27:
	lw	$2,20($fp)
	nop
	lw	$2,0($2)
	nop
	sw	$2,32($fp)
	lw	$4,32($fp)
	jal	xtoa
	nop

	move	$4,$2
	jal	puts
	nop

	lui	$2,%hi($LC1)
	addiu	$4,$2,%lo($LC1)
	jal	puts
	nop

	lw	$2,20($fp)
	nop
	addiu	$2,$2,4
	sw	$2,20($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L26:
	lw	$2,16($fp)
	lw	$3,28($fp)
	nop
	sltu	$2,$2,$3
	bne	$2,$0,$L27
	nop

	li	$4,3			# 0x3
	jal	putc_uart
	nop

	nop
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_l_func
	.size	_l_func, .-_l_func
	.align	2
	.globl	_j_func
	.set	nomips16
	.set	nomicromips
	.ent	_j_func
	.type	_j_func, @function
_j_func:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	jal	getnum
	nop

	sw	$2,16($fp)
	li	$4,6			# 0x6
	jal	putc_uart
	nop

	lw	$2,16($fp)
	nop
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
	.end	_j_func
	.size	_j_func, .-_j_func
	.align	2
	.globl	_S_func
	.set	nomips16
	.set	nomicromips
	.ent	_S_func
	.type	_S_func, @function
_S_func:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	jal	getch
	nop

	sb	$2,16($fp)
	lb	$3,16($fp)
	li	$2,83			# 0x53
	bne	$3,$2,$L31
	nop

	li	$2,728			# 0x2d8
	sw	$2,20($fp)
	jal	getch
	nop

	move	$4,$2
	lw	$2,20($fp)
	li	$3,268500992			# 0x10010000
	ori	$5,$3,0xf3f0
	jalr	$2
	nop

$L31:
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	_S_func
	.size	_S_func, .-_S_func
	.rdata
	.align	2
$LC2:
	.ascii	"\015start connecting probe \000"
	.align	2
$LC3:
	.ascii	".\000"
	.align	2
$LC4:
	.ascii	"\015probe connected\012\000"
	.text
	.align	2
	.globl	_ProbeConn_func
	.set	nomips16
	.set	nomicromips
	.ent	_ProbeConn_func
	.type	_ProbeConn_func, @function
_ProbeConn_func:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$0,16($fp)
	lui	$2,%hi($LC2)
	addiu	$4,$2,%lo($LC2)
	jal	puts
	nop

	b	$L33
	nop

$L36:
	jal	probe_setup
	nop

	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
	lw	$3,16($fp)
	li	$2,1000			# 0x3e8
	bne	$3,$2,$L34
	nop

	lui	$2,%hi($LC3)
	addiu	$4,$2,%lo($LC3)
	jal	puts
	nop

	b	$L33
	nop

$L34:
	lw	$3,16($fp)
	li	$2,65536			# 0x10000
	ori	$2,$2,0x86a0
	beq	$3,$2,$L37
	nop

$L33:
	jal	kbhit
	nop

	beq	$2,$0,$L36
	nop

	b	$L35
	nop

$L37:
	nop
$L35:
	lui	$2,%hi($LC4)
	addiu	$4,$2,%lo($LC4)
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
	.end	_ProbeConn_func
	.size	_ProbeConn_func, .-_ProbeConn_func
	.align	2
	.globl	gdb
	.set	nomips16
	.set	nomicromips
	.ent	gdb
	.type	gdb, @function
gdb:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
$L51:
	jal	getch
	nop

	sw	$2,16($fp)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,-80
	sltu	$3,$2,40
	beq	$3,$0,$L51
	nop

	sll	$3,$2,2
	lui	$2,%hi($L41)
	addiu	$2,$2,%lo($L41)
	addu	$2,$3,$2
	lw	$2,0($2)
	nop
	jr	$2
	nop

	.rdata
	.align	2
	.align	2
$L41:
	.word	$L40
	.word	$L51
	.word	$L42
	.word	$L43
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L52
	.word	$L51
	.word	$L51
	.word	$L45
	.word	$L51
	.word	$L46
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L47
	.word	$L48
	.word	$L51
	.word	$L51
	.word	$L51
	.word	$L49
	.text
$L49:
	jal	_w_func
	nop

	b	$L39
	nop

$L47:
	jal	_r_func
	nop

	b	$L39
	nop

$L42:
	jal	_R_func
	nop

	b	$L39
	nop

$L48:
	jal	_s_func
	nop

	b	$L39
	nop

$L46:
	jal	_l_func
	nop

	b	$L39
	nop

$L45:
	jal	_j_func
	nop

	b	$L39
	nop

$L43:
	jal	_S_func
	nop

	b	$L39
	nop

$L40:
	jal	_ProbeConn_func
	nop

	nop
$L39:
	b	$L51
	nop

$L52:
	nop
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	gdb
	.size	gdb, .-gdb
	.align	2
	.globl	interrupt
	.set	nomips16
	.set	nomicromips
	.ent	interrupt
	.type	interrupt, @function
interrupt:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	li	$2,528482304			# 0x1f800000
	ori	$2,$2,0x707
	lw	$2,0($2)
	nop
	sw	$2,20($fp)
	lw	$2,20($fp)
	nop
	andi	$2,$2,0x1
	sw	$2,24($fp)
	lw	$2,20($fp)
	nop
	andi	$2,$2,0x10
	sw	$2,16($fp)
	jal	read_uart
	nop

	sw	$2,28($fp)
	lw	$2,16($fp)
	nop
	bne	$2,$0,$L54
	nop

	lw	$2,24($fp)
	nop
	blez	$2,$L54
	nop

	lw	$3,28($fp)
	li	$2,6			# 0x6
	bne	$3,$2,$L54
	nop

	li	$2,1			# 0x1
	sw	$2,16($fp)
$L54:
	lw	$2,16($fp)
	nop
	blez	$2,$L55
	nop

	li	$4,5			# 0x5
	jal	putc_uart
	nop

	jal	gdb
	nop

	b	$L57
	nop

$L55:
	li	$2,16777216			# 0x1000000
	ori	$2,$2,0x1ffc
	li	$3,1			# 0x1
	sw	$3,0($2)
	jal	user_interrupt
	nop

$L57:
	nop
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	interrupt
	.size	interrupt, .-interrupt
	.ident	"GCC: (GNU) 7.3.0"
