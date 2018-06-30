	.file	1 "DES.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.text
	.align	2
	.globl	DES_generateSubKeys
	.set	nomips16
	.set	nomicromips
	.ent	DES_generateSubKeys
	.type	DES_generateSubKeys, @function
DES_generateSubKeys:
	.frame	$sp,144,$31		# vars= 136, regs= 1/0, args= 0, gp= 0
	.mask	0x00010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-144
	lui	$2,%hi(subKeys.1473)
	move	$7,$0
	move	$6,$0
	lui	$12,%hi(__permuted_key_table_PC1__+1)
	sw	$7,%lo(subKeys.1473+4)($2)
	sw	$16,140($sp)
	sw	$6,%lo(subKeys.1473)($2)
	addiu	$12,$12,%lo(__permuted_key_table_PC1__+1)
	li	$9,7			# 0x7
	move	$25,$0
	move	$15,$0
	move	$16,$0
	move	$14,$0
	move	$7,$0
	li	$13,1			# 0x1
	b	$L7
	li	$24,56			# 0x38

$L27:
	srl	$3,$3,$9
	sltu	$6,$7,24
	sll	$8,$14,1
	sll	$9,$15,1
	bne	$6,$0,$L26
	andi	$3,$3,0x1

$L4:
	addiu	$7,$7,1
	andi	$7,$7,0x00ff
	or	$14,$8,$3
	beq	$7,$24,$L6
	li	$16,1			# 0x1

$L28:
	lbu	$9,0($12)
	addiu	$12,$12,1
$L7:
	addiu	$11,$9,-32
	sll	$3,$13,$11
	sll	$8,$13,$9
	sltu	$10,$9,32
	and	$6,$3,$5
	bne	$10,$0,$L27
	and	$3,$8,$4

	srl	$3,$6,$11
	sltu	$6,$7,24
	sll	$8,$14,1
	sll	$9,$15,1
	beq	$6,$0,$L4
	andi	$3,$3,0x1

$L26:
	addiu	$7,$7,1
	andi	$7,$7,0x00ff
	or	$15,$9,$3
	bne	$7,$24,$L28
	li	$25,1			# 0x1

$L6:
	bne	$16,$0,$L29
	li	$3,268369920			# 0xfff0000

	move	$14,$0
	move	$3,$0
$L8:
	bne	$25,$0,$L23
	nop

	lui	$2,%hi(subKeys.1473)
	addiu	$2,$2,%lo(subKeys.1473)
$L9:
	lw	$4,4($2)
	lui	$9,%hi(__keyPair_leftshift_table__+2)
	sll	$4,$4,4
	or	$4,$4,$14
	sw	$3,4($sp)
	sw	$4,0($sp)
	move	$5,$sp
	addiu	$9,$9,%lo(__keyPair_leftshift_table__+2)
	addiu	$11,$sp,128
	li	$6,1			# 0x1
	b	$L11
	li	$10,28			# 0x1c

$L30:
	lbu	$6,0($9)
	addiu	$9,$9,1
$L11:
	lw	$7,4($5)
	addiu	$3,$6,4
	lw	$8,0($5)
	subu	$6,$10,$6
	sll	$4,$4,$3
	sll	$3,$7,$3
	srl	$8,$8,$6
	srl	$4,$4,4
	srl	$3,$3,4
	srl	$6,$7,$6
	or	$4,$4,$8
	or	$3,$3,$6
	sw	$4,8($5)
	sw	$3,12($5)
	addiu	$5,$5,8
	bne	$5,$11,$L30
	lui	$14,%hi(__permuted_key_table_PC2__+1)

	lui	$9,%hi(subKeys.1473+8)
	addiu	$9,$9,%lo(subKeys.1473+8)
	addiu	$12,$sp,8
	addiu	$15,$2,136
	addiu	$14,$14,%lo(__permuted_key_table_PC2__+1)
	li	$10,1			# 0x1
	li	$13,48			# 0x30
$L18:
	move	$4,$0
	move	$5,$0
	sw	$4,0($9)
	sw	$5,4($9)
	move	$8,$14
	li	$4,42			# 0x2a
	b	$L17
	move	$3,$0

$L32:
	lw	$5,4($12)
	nop
	and	$7,$7,$5
	sltu	$5,$3,16
	bne	$5,$0,$L31
	srl	$4,$7,$4

$L14:
	lw	$5,0($9)
	addiu	$3,$3,1
	sll	$5,$5,1
	or	$4,$5,$4
	andi	$3,$3,0x00ff
	beq	$3,$13,$L16
	sw	$4,0($9)

$L33:
	lbu	$4,0($8)
	addiu	$8,$8,1
$L17:
	addiu	$6,$4,-28
	sltu	$11,$4,28
	sll	$5,$10,$6
	bne	$11,$0,$L32
	sll	$7,$10,$4

	lw	$4,0($12)
	nop
	and	$4,$5,$4
	sltu	$5,$3,16
	beq	$5,$0,$L14
	srl	$4,$4,$6

$L31:
	lw	$5,4($9)
	addiu	$3,$3,1
	sll	$5,$5,1
	or	$4,$5,$4
	andi	$3,$3,0x00ff
	bne	$3,$13,$L33
	sw	$4,4($9)

$L16:
	addiu	$9,$9,8
	bne	$9,$15,$L18
	addiu	$12,$12,8

	lw	$16,140($sp)
	jr	$31
	addiu	$sp,$sp,144

$L29:
	ori	$3,$3,0xffff
	sw	$14,%lo(subKeys.1473)($2)
	and	$3,$14,$3
	b	$L8
	srl	$14,$14,28

$L23:
	addiu	$2,$2,%lo(subKeys.1473)
	b	$L9
	sw	$15,4($2)

	.set	macro
	.set	reorder
	.end	DES_generateSubKeys
	.size	DES_generateSubKeys, .-DES_generateSubKeys
	.align	2
	.globl	__calculate_R_part__
	.set	nomips16
	.set	nomicromips
	.ent	__calculate_R_part__
	.type	__calculate_R_part__, @function
__calculate_R_part__:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(__E_BIT_SELECTION_TABLE__)
	addiu	$10,$2,%lo(__E_BIT_SELECTION_TABLE__)
	lui	$2,%hi(__E_BIT_SELECTION_TABLE__+1)
	addiu	$2,$2,%lo(__E_BIT_SELECTION_TABLE__+1)
	addiu	$12,$10,16
	move	$9,$0
	move	$11,$0
	b	$L37
	li	$8,1			# 0x1

$L35:
	lbu	$9,0($2)
	addiu	$2,$2,1
$L37:
	sll	$3,$8,$9
	and	$3,$3,$4
	srl	$3,$3,$9
	sll	$11,$11,1
	bne	$12,$2,$L35
	or	$11,$3,$11

	lui	$9,%hi(__E_BIT_SELECTION_TABLE__+17)
	addiu	$2,$10,48
	addiu	$9,$9,%lo(__E_BIT_SELECTION_TABLE__+17)
	li	$10,20			# 0x14
	move	$8,$0
	b	$L36
	li	$12,1			# 0x1

$L43:
	lbu	$10,0($9)
	addiu	$9,$9,1
$L36:
	sll	$3,$12,$10
	and	$3,$3,$4
	srl	$3,$3,$10
	sll	$8,$8,1
	bne	$2,$9,$L43
	or	$8,$3,$8

	xor	$11,$11,$7
	andi	$11,$11,0xffff
	srl	$2,$11,4
	andi	$7,$2,0x3f
	xor	$8,$8,$6
	srl	$9,$11,10
	srl	$6,$11,14
	sll	$3,$11,2
	andi	$9,$9,0x1
	srl	$4,$7,4
	srl	$10,$8,30
	andi	$6,$6,0x2
	andi	$3,$3,0x3c
	or	$3,$3,$10
	or	$6,$6,$9
	andi	$2,$2,0x1
	andi	$4,$4,0x2
	lui	$10,%hi(__S_TABLE__)
	addiu	$10,$10,%lo(__S_TABLE__)
	or	$4,$4,$2
	srl	$11,$11,11
	srl	$2,$3,4
	sll	$6,$6,4
	andi	$9,$3,0x1
	addu	$6,$10,$6
	andi	$11,$11,0xf
	srl	$7,$7,1
	sll	$4,$4,4
	andi	$2,$2,0x2
	andi	$7,$7,0xf
	or	$2,$2,$9
	addu	$11,$6,$11
	addu	$4,$10,$4
	lbu	$6,0($11)
	addu	$4,$4,$7
	srl	$3,$3,1
	sll	$2,$2,4
	lbu	$7,64($4)
	andi	$3,$3,0xf
	addu	$2,$10,$2
	andi	$4,$6,0xf
	addu	$2,$2,$3
	andi	$7,$7,0xf
	sll	$3,$4,4
	lbu	$4,128($2)
	or	$2,$7,$3
	sll	$2,$2,4
	andi	$7,$4,0xf
	or	$7,$7,$2
	li	$9,24			# 0x18
	li	$6,3			# 0x3
	li	$13,63			# 0x3f
	li	$12,8			# 0x8
$L39:
	sll	$2,$13,$9
	and	$2,$2,$8
	srl	$2,$2,$9
	srl	$4,$2,4
	andi	$11,$2,0x1
	andi	$4,$4,0x2
	sll	$3,$6,2
	or	$4,$4,$11
	addu	$3,$3,$4
	srl	$2,$2,1
	sll	$3,$3,4
	andi	$2,$2,0xf
	addu	$3,$10,$3
	addu	$2,$3,$2
	lbu	$2,0($2)
	sll	$7,$7,4
	andi	$2,$2,0xf
	addiu	$6,$6,1
	or	$7,$2,$7
	bne	$6,$12,$L39
	addiu	$9,$9,-6

	lui	$4,%hi(__PERMUTATION_P_TABLE__+1)
	lui	$8,%hi(__PERMUTATION_P_TABLE__+32)
	addiu	$4,$4,%lo(__PERMUTATION_P_TABLE__+1)
	addiu	$8,$8,%lo(__PERMUTATION_P_TABLE__+32)
	li	$6,16			# 0x10
	move	$2,$0
	b	$L41
	li	$9,1			# 0x1

$L44:
	lbu	$6,0($4)
	addiu	$4,$4,1
$L41:
	sll	$3,$9,$6
	and	$3,$3,$7
	srl	$3,$3,$6
	sll	$2,$2,1
	bne	$8,$4,$L44
	or	$2,$3,$2

	jr	$31
	xor	$2,$2,$5

	.set	macro
	.set	reorder
	.end	__calculate_R_part__
	.size	__calculate_R_part__, .-__calculate_R_part__
	.align	2
	.globl	DES_process
	.set	nomips16
	.set	nomicromips
	.ent	DES_process
	.type	DES_process, @function
DES_process:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$13,%hi(__permuted_message_table_IP__)
	addiu	$sp,$sp,-24
	addiu	$13,$13,%lo(__permuted_message_table_IP__)
	move	$3,$0
	move	$2,$0
	lui	$8,%hi(__permuted_message_table_IP__+1)
	move	$15,$4
	sw	$31,20($sp)
	lw	$24,40($sp)
	sw	$3,4($4)
	sw	$2,0($4)
	lbu	$9,47($sp)
	addiu	$8,$8,%lo(__permuted_message_table_IP__+1)
	addiu	$14,$13,32
	li	$4,6			# 0x6
	move	$5,$0
	b	$L49
	li	$11,1			# 0x1

$L67:
	beq	$14,$8,$L48
	or	$5,$3,$5

$L68:
	lbu	$4,0($8)
	addiu	$8,$8,1
$L49:
	addiu	$10,$4,-32
	sll	$3,$11,$4
	sll	$2,$11,$10
	and	$3,$3,$6
	and	$2,$2,$7
	sltu	$12,$4,32
	srl	$3,$3,$4
	srl	$2,$2,$10
	bne	$12,$0,$L67
	sll	$5,$5,1

	bne	$14,$8,$L68
	or	$5,$2,$5

$L48:
	lui	$8,%hi(__permuted_message_table_IP__+33)
	addiu	$8,$8,%lo(__permuted_message_table_IP__+33)
	addiu	$13,$13,64
	li	$4,7			# 0x7
	move	$14,$0
	b	$L53
	li	$11,1			# 0x1

$L69:
	beq	$13,$8,$L52
	or	$14,$3,$14

$L70:
	lbu	$4,0($8)
	addiu	$8,$8,1
$L53:
	addiu	$10,$4,-32
	sll	$3,$11,$4
	sll	$2,$11,$10
	and	$3,$3,$6
	and	$2,$2,$7
	sltu	$12,$4,32
	srl	$3,$3,$4
	srl	$2,$2,$10
	bne	$12,$0,$L69
	sll	$14,$14,1

	bne	$13,$8,$L70
	or	$14,$2,$14

$L52:
	li	$2,1			# 0x1
	beq	$9,$2,$L54
	move	$4,$14

	addiu	$25,$24,8
	b	$L55
	addiu	$24,$24,136

$L71:
	move	$14,$2
$L55:
	lw	$7,4($25)
	lw	$6,0($25)
	sw	$14,4($15)
	jal	__calculate_R_part__
	addiu	$25,$25,8

	move	$4,$2
	move	$5,$14
	bne	$25,$24,$L71
	sw	$2,0($15)

	lui	$11,%hi(__PERMUTATION_P_1_TABLE__)
$L77:
	addiu	$11,$11,%lo(__PERMUTATION_P_1_TABLE__)
	lui	$7,%hi(__PERMUTATION_P_1_TABLE__+1)
	addiu	$7,$7,%lo(__PERMUTATION_P_1_TABLE__+1)
	addiu	$12,$11,32
	li	$5,24			# 0x18
	move	$6,$0
	b	$L61
	li	$9,1			# 0x1

$L72:
	beq	$12,$7,$L60
	or	$6,$4,$6

$L73:
	lbu	$5,0($7)
	addiu	$7,$7,1
$L61:
	addiu	$8,$5,-32
	sll	$4,$9,$5
	sll	$3,$9,$8
	and	$4,$4,$14
	and	$3,$3,$2
	sltu	$10,$5,32
	srl	$4,$4,$5
	srl	$3,$3,$8
	bne	$10,$0,$L72
	sll	$6,$6,1

	bne	$12,$7,$L73
	or	$6,$3,$6

$L60:
	lui	$7,%hi(__PERMUTATION_P_1_TABLE__+33)
	sw	$6,4($15)
	addiu	$7,$7,%lo(__PERMUTATION_P_1_TABLE__+33)
	addiu	$11,$11,64
	li	$5,28			# 0x1c
	move	$6,$0
	b	$L65
	li	$9,1			# 0x1

$L74:
	beq	$11,$7,$L64
	or	$6,$4,$6

$L75:
	lbu	$5,0($7)
	addiu	$7,$7,1
$L65:
	addiu	$8,$5,-32
	sll	$4,$9,$5
	sll	$3,$9,$8
	and	$4,$4,$14
	and	$3,$3,$2
	sltu	$10,$5,32
	srl	$4,$4,$5
	srl	$3,$3,$8
	bne	$10,$0,$L74
	sll	$6,$6,1

	bne	$11,$7,$L75
	or	$6,$3,$6

$L64:
	lw	$31,20($sp)
	sw	$6,0($15)
	move	$2,$15
	jr	$31
	addiu	$sp,$sp,24

$L54:
	b	$L57
	addiu	$25,$24,128

$L76:
	move	$14,$2
$L57:
	lw	$7,4($25)
	lw	$6,0($25)
	sw	$14,4($15)
	jal	__calculate_R_part__
	addiu	$25,$25,-8

	move	$4,$2
	move	$5,$14
	bne	$24,$25,$L76
	sw	$2,0($15)

	b	$L77
	lui	$11,%hi(__PERMUTATION_P_1_TABLE__)

	.set	macro
	.set	reorder
	.end	DES_process
	.size	DES_process, .-DES_process
	.align	2
	.globl	DES
	.set	nomips16
	.set	nomicromips
	.ent	DES
	.type	DES, @function
DES:
	.frame	$sp,40,$31		# vars= 8, regs= 2/0, args= 24, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$16,32($sp)
	lw	$5,60($sp)
	move	$16,$4
	lw	$4,56($sp)
	sw	$31,36($sp)
	sw	$7,28($sp)
	jal	DES_generateSubKeys
	sw	$6,24($sp)

	sw	$2,16($sp)
	lbu	$2,67($sp)
	lw	$7,28($sp)
	lw	$6,24($sp)
	sw	$2,20($sp)
	jal	DES_process
	move	$4,$16

	lw	$31,36($sp)
	move	$2,$16
	lw	$16,32($sp)
	jr	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	DES
	.size	DES, .-DES
	.local	subKeys.1473
	.comm	subKeys.1473,136,8
	.globl	__PERMUTATION_P_1_TABLE__
	.rdata
	.align	2
	.type	__PERMUTATION_P_1_TABLE__, @object
	.size	__PERMUTATION_P_1_TABLE__, 64
__PERMUTATION_P_1_TABLE__:
	.byte	24
	.byte	56
	.byte	16
	.byte	48
	.byte	8
	.byte	40
	.byte	0
	.byte	32
	.byte	25
	.byte	57
	.byte	17
	.byte	49
	.byte	9
	.byte	41
	.byte	1
	.byte	33
	.byte	26
	.byte	58
	.byte	18
	.byte	50
	.byte	10
	.byte	42
	.byte	2
	.byte	34
	.byte	27
	.byte	59
	.byte	19
	.byte	51
	.byte	11
	.byte	43
	.byte	3
	.byte	35
	.byte	28
	.byte	60
	.byte	20
	.byte	52
	.byte	12
	.byte	44
	.byte	4
	.byte	36
	.byte	29
	.byte	61
	.byte	21
	.byte	53
	.byte	13
	.byte	45
	.byte	5
	.byte	37
	.byte	30
	.byte	62
	.byte	22
	.byte	54
	.byte	14
	.byte	46
	.byte	6
	.byte	38
	.byte	31
	.byte	63
	.byte	23
	.byte	55
	.byte	15
	.byte	47
	.byte	7
	.byte	39
	.globl	__PERMUTATION_P_TABLE__
	.align	2
	.type	__PERMUTATION_P_TABLE__, @object
	.size	__PERMUTATION_P_TABLE__, 32
__PERMUTATION_P_TABLE__:
	.byte	16
	.byte	25
	.byte	12
	.byte	11
	.byte	3
	.byte	20
	.byte	4
	.byte	15
	.byte	31
	.byte	17
	.byte	9
	.byte	6
	.byte	27
	.byte	14
	.byte	1
	.byte	22
	.byte	30
	.byte	24
	.byte	8
	.byte	18
	.byte	0
	.byte	5
	.byte	29
	.byte	23
	.byte	13
	.byte	19
	.byte	2
	.byte	26
	.byte	10
	.byte	21
	.byte	28
	.byte	7
	.globl	__S_TABLE__
	.align	2
	.type	__S_TABLE__, @object
	.size	__S_TABLE__, 512
__S_TABLE__:
	.byte	14
	.byte	4
	.byte	13
	.byte	1
	.byte	2
	.byte	15
	.byte	11
	.byte	8
	.byte	3
	.byte	10
	.byte	6
	.byte	12
	.byte	5
	.byte	9
	.byte	0
	.byte	7
	.byte	0
	.byte	15
	.byte	7
	.byte	4
	.byte	14
	.byte	2
	.byte	13
	.byte	1
	.byte	10
	.byte	6
	.byte	12
	.byte	11
	.byte	9
	.byte	5
	.byte	3
	.byte	8
	.byte	4
	.byte	1
	.byte	14
	.byte	8
	.byte	13
	.byte	6
	.byte	2
	.byte	11
	.byte	15
	.byte	12
	.byte	9
	.byte	7
	.byte	3
	.byte	10
	.byte	5
	.byte	0
	.byte	15
	.byte	12
	.byte	8
	.byte	2
	.byte	4
	.byte	9
	.byte	1
	.byte	7
	.byte	5
	.byte	11
	.byte	3
	.byte	14
	.byte	10
	.byte	0
	.byte	6
	.byte	13
	.byte	15
	.byte	1
	.byte	8
	.byte	14
	.byte	6
	.byte	11
	.byte	3
	.byte	4
	.byte	9
	.byte	7
	.byte	2
	.byte	13
	.byte	12
	.byte	0
	.byte	5
	.byte	10
	.byte	3
	.byte	13
	.byte	4
	.byte	7
	.byte	15
	.byte	2
	.byte	8
	.byte	14
	.byte	12
	.byte	0
	.byte	1
	.byte	10
	.byte	6
	.byte	9
	.byte	11
	.byte	5
	.byte	0
	.byte	14
	.byte	7
	.byte	11
	.byte	10
	.byte	4
	.byte	13
	.byte	1
	.byte	5
	.byte	8
	.byte	12
	.byte	6
	.byte	9
	.byte	3
	.byte	2
	.byte	15
	.byte	13
	.byte	8
	.byte	10
	.byte	1
	.byte	3
	.byte	15
	.byte	4
	.byte	2
	.byte	11
	.byte	6
	.byte	7
	.byte	12
	.byte	0
	.byte	5
	.byte	14
	.byte	9
	.byte	10
	.byte	0
	.byte	9
	.byte	14
	.byte	6
	.byte	3
	.byte	15
	.byte	5
	.byte	1
	.byte	13
	.byte	12
	.byte	7
	.byte	11
	.byte	4
	.byte	2
	.byte	8
	.byte	13
	.byte	7
	.byte	0
	.byte	9
	.byte	3
	.byte	4
	.byte	6
	.byte	10
	.byte	2
	.byte	8
	.byte	5
	.byte	14
	.byte	12
	.byte	11
	.byte	15
	.byte	1
	.byte	13
	.byte	6
	.byte	4
	.byte	9
	.byte	8
	.byte	15
	.byte	3
	.byte	0
	.byte	11
	.byte	1
	.byte	2
	.byte	12
	.byte	5
	.byte	10
	.byte	14
	.byte	7
	.byte	1
	.byte	10
	.byte	13
	.byte	0
	.byte	6
	.byte	9
	.byte	8
	.byte	7
	.byte	4
	.byte	15
	.byte	14
	.byte	3
	.byte	11
	.byte	5
	.byte	2
	.byte	12
	.byte	7
	.byte	13
	.byte	14
	.byte	3
	.byte	0
	.byte	6
	.byte	9
	.byte	10
	.byte	1
	.byte	2
	.byte	8
	.byte	5
	.byte	11
	.byte	12
	.byte	4
	.byte	15
	.byte	13
	.byte	8
	.byte	11
	.byte	5
	.byte	6
	.byte	15
	.byte	0
	.byte	3
	.byte	4
	.byte	7
	.byte	2
	.byte	12
	.byte	1
	.byte	10
	.byte	14
	.byte	9
	.byte	10
	.byte	6
	.byte	9
	.byte	0
	.byte	12
	.byte	11
	.byte	7
	.byte	13
	.byte	15
	.byte	1
	.byte	3
	.byte	14
	.byte	5
	.byte	2
	.byte	8
	.byte	4
	.byte	3
	.byte	15
	.byte	0
	.byte	6
	.byte	10
	.byte	1
	.byte	13
	.byte	8
	.byte	9
	.byte	4
	.byte	5
	.byte	11
	.byte	12
	.byte	7
	.byte	2
	.byte	14
	.byte	2
	.byte	12
	.byte	4
	.byte	1
	.byte	7
	.byte	10
	.byte	11
	.byte	6
	.byte	8
	.byte	5
	.byte	3
	.byte	15
	.byte	13
	.byte	0
	.byte	14
	.byte	9
	.byte	14
	.byte	11
	.byte	2
	.byte	12
	.byte	4
	.byte	7
	.byte	13
	.byte	1
	.byte	5
	.byte	0
	.byte	15
	.byte	10
	.byte	3
	.byte	9
	.byte	8
	.byte	6
	.byte	4
	.byte	2
	.byte	1
	.byte	11
	.byte	10
	.byte	13
	.byte	7
	.byte	8
	.byte	15
	.byte	9
	.byte	12
	.byte	5
	.byte	6
	.byte	3
	.byte	0
	.byte	14
	.byte	11
	.byte	8
	.byte	12
	.byte	7
	.byte	1
	.byte	14
	.byte	2
	.byte	13
	.byte	6
	.byte	15
	.byte	0
	.byte	9
	.byte	10
	.byte	4
	.byte	5
	.byte	3
	.byte	12
	.byte	1
	.byte	10
	.byte	15
	.byte	9
	.byte	2
	.byte	6
	.byte	8
	.byte	0
	.byte	13
	.byte	3
	.byte	4
	.byte	14
	.byte	7
	.byte	5
	.byte	11
	.byte	10
	.byte	15
	.byte	4
	.byte	2
	.byte	7
	.byte	12
	.byte	9
	.byte	5
	.byte	6
	.byte	1
	.byte	13
	.byte	14
	.byte	0
	.byte	11
	.byte	3
	.byte	8
	.byte	9
	.byte	14
	.byte	15
	.byte	5
	.byte	2
	.byte	8
	.byte	12
	.byte	3
	.byte	7
	.byte	0
	.byte	4
	.byte	10
	.byte	1
	.byte	13
	.byte	11
	.byte	6
	.byte	4
	.byte	3
	.byte	2
	.byte	12
	.byte	9
	.byte	5
	.byte	15
	.byte	10
	.byte	11
	.byte	14
	.byte	1
	.byte	7
	.byte	6
	.byte	0
	.byte	8
	.byte	13
	.byte	4
	.byte	11
	.byte	2
	.byte	14
	.byte	15
	.byte	0
	.byte	8
	.byte	13
	.byte	3
	.byte	12
	.byte	9
	.byte	7
	.byte	5
	.byte	10
	.byte	6
	.byte	1
	.byte	13
	.byte	0
	.byte	11
	.byte	7
	.byte	4
	.byte	9
	.byte	1
	.byte	10
	.byte	14
	.byte	3
	.byte	5
	.byte	12
	.byte	2
	.byte	15
	.byte	8
	.byte	6
	.byte	1
	.byte	4
	.byte	11
	.byte	13
	.byte	12
	.byte	3
	.byte	7
	.byte	14
	.byte	10
	.byte	15
	.byte	6
	.byte	8
	.byte	0
	.byte	5
	.byte	9
	.byte	2
	.byte	6
	.byte	11
	.byte	13
	.byte	8
	.byte	1
	.byte	4
	.byte	10
	.byte	7
	.byte	9
	.byte	5
	.byte	0
	.byte	15
	.byte	14
	.byte	2
	.byte	3
	.byte	12
	.byte	13
	.byte	2
	.byte	8
	.byte	4
	.byte	6
	.byte	15
	.byte	11
	.byte	1
	.byte	10
	.byte	9
	.byte	3
	.byte	14
	.byte	5
	.byte	0
	.byte	12
	.byte	7
	.byte	1
	.byte	15
	.byte	13
	.byte	8
	.byte	10
	.byte	3
	.byte	7
	.byte	4
	.byte	12
	.byte	5
	.byte	6
	.byte	11
	.byte	0
	.byte	14
	.byte	9
	.byte	2
	.byte	7
	.byte	11
	.byte	4
	.byte	1
	.byte	9
	.byte	12
	.byte	14
	.byte	2
	.byte	0
	.byte	6
	.byte	10
	.byte	13
	.byte	15
	.byte	3
	.byte	5
	.byte	8
	.byte	2
	.byte	1
	.byte	14
	.byte	7
	.byte	4
	.byte	10
	.byte	8
	.byte	13
	.byte	15
	.byte	12
	.byte	9
	.byte	0
	.byte	3
	.byte	5
	.byte	6
	.byte	11
	.globl	__E_BIT_SELECTION_TABLE__
	.align	2
	.type	__E_BIT_SELECTION_TABLE__, @object
	.size	__E_BIT_SELECTION_TABLE__, 48
__E_BIT_SELECTION_TABLE__:
	.byte	0
	.byte	31
	.byte	30
	.byte	29
	.byte	28
	.byte	27
	.byte	28
	.byte	27
	.byte	26
	.byte	25
	.byte	24
	.byte	23
	.byte	24
	.byte	23
	.byte	22
	.byte	21
	.byte	20
	.byte	19
	.byte	20
	.byte	19
	.byte	18
	.byte	17
	.byte	16
	.byte	15
	.byte	16
	.byte	15
	.byte	14
	.byte	13
	.byte	12
	.byte	11
	.byte	12
	.byte	11
	.byte	10
	.byte	9
	.byte	8
	.byte	7
	.byte	8
	.byte	7
	.byte	6
	.byte	5
	.byte	4
	.byte	3
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	0
	.byte	31
	.globl	__permuted_message_table_IP__
	.align	2
	.type	__permuted_message_table_IP__, @object
	.size	__permuted_message_table_IP__, 64
__permuted_message_table_IP__:
	.byte	6
	.byte	14
	.byte	22
	.byte	30
	.byte	38
	.byte	46
	.byte	54
	.byte	62
	.byte	4
	.byte	12
	.byte	20
	.byte	28
	.byte	36
	.byte	44
	.byte	52
	.byte	60
	.byte	2
	.byte	10
	.byte	18
	.byte	26
	.byte	34
	.byte	42
	.byte	50
	.byte	58
	.byte	0
	.byte	8
	.byte	16
	.byte	24
	.byte	32
	.byte	40
	.byte	48
	.byte	56
	.byte	7
	.byte	15
	.byte	23
	.byte	31
	.byte	39
	.byte	47
	.byte	55
	.byte	63
	.byte	5
	.byte	13
	.byte	21
	.byte	29
	.byte	37
	.byte	45
	.byte	53
	.byte	61
	.byte	3
	.byte	11
	.byte	19
	.byte	27
	.byte	35
	.byte	43
	.byte	51
	.byte	59
	.byte	1
	.byte	9
	.byte	17
	.byte	25
	.byte	33
	.byte	41
	.byte	49
	.byte	57
	.globl	__permuted_key_table_PC2__
	.align	2
	.type	__permuted_key_table_PC2__, @object
	.size	__permuted_key_table_PC2__, 48
__permuted_key_table_PC2__:
	.byte	42
	.byte	39
	.byte	45
	.byte	32
	.byte	55
	.byte	51
	.byte	53
	.byte	28
	.byte	41
	.byte	50
	.byte	35
	.byte	46
	.byte	33
	.byte	37
	.byte	44
	.byte	52
	.byte	30
	.byte	48
	.byte	40
	.byte	49
	.byte	29
	.byte	36
	.byte	43
	.byte	54
	.byte	15
	.byte	4
	.byte	25
	.byte	19
	.byte	9
	.byte	1
	.byte	26
	.byte	16
	.byte	5
	.byte	11
	.byte	23
	.byte	8
	.byte	12
	.byte	7
	.byte	17
	.byte	0
	.byte	22
	.byte	3
	.byte	10
	.byte	14
	.byte	6
	.byte	20
	.byte	27
	.byte	24
	.globl	__keyPair_leftshift_table__
	.align	2
	.type	__keyPair_leftshift_table__, @object
	.size	__keyPair_leftshift_table__, 17
__keyPair_leftshift_table__:
	.byte	0
	.byte	1
	.byte	1
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.globl	__permuted_key_table_PC1__
	.align	2
	.type	__permuted_key_table_PC1__, @object
	.size	__permuted_key_table_PC1__, 56
__permuted_key_table_PC1__:
	.byte	7
	.byte	15
	.byte	23
	.byte	31
	.byte	39
	.byte	47
	.byte	55
	.byte	63
	.byte	6
	.byte	14
	.byte	22
	.byte	30
	.byte	28
	.byte	46
	.byte	54
	.byte	62
	.byte	5
	.byte	13
	.byte	21
	.byte	29
	.byte	37
	.byte	45
	.byte	53
	.byte	61
	.byte	4
	.byte	12
	.byte	20
	.byte	28
	.byte	1
	.byte	9
	.byte	17
	.byte	25
	.byte	33
	.byte	41
	.byte	49
	.byte	57
	.byte	2
	.byte	10
	.byte	18
	.byte	26
	.byte	34
	.byte	42
	.byte	50
	.byte	58
	.byte	3
	.byte	11
	.byte	19
	.byte	27
	.byte	35
	.byte	43
	.byte	51
	.byte	59
	.byte	36
	.byte	44
	.byte	52
	.byte	60
	.ident	"GCC: (GNU) 7.3.0"
