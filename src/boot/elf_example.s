10000000:	00000000 	nop
10000004:	08000007 	j	0x1000001c    // jump to pre_load
10000008:	00000000 	nop
1000000c:	080000cf 	j	0x1000033c    // jump to interrupt service routine
10000010:	00000000 	nop
10000014:	080000cf 	j	0x1000033c    // jump to interrupt service routine
10000018:	00000000 	nop
1000001c:	3c1c0000 	lui	gp,0x0        // pre_load
10000020:	379c0000 	ori	gp,gp,0x0
10000024:	3c040000 	lui	a0,0x0
10000028:	34840000 	ori	a0,a0,0x0
1000002c:	3c050000 	lui	a1,0x0
10000030:	34a50000 	ori	a1,a1,0x0
10000034:	3c060000 	lui	a2,0x0
10000038:	34c60000 	ori	a2,a2,0x0
1000003c:	10000007 	b	0x1000005c
10000040:	00000000 	nop
10000044:	8c830000 	lw	v1,0(a0)
10000048:	00000000 	nop
1000004c:	acc30000 	sw	v1,0(a2)
10000050:	00000000 	nop
10000054:	24c60004 	addiu	a2,a2,4
10000058:	24840004 	addiu	a0,a0,4
1000005c:	0085182a 	slt	v1,a0,a1
10000060:	1460fff8 	bnez	v1,0x10000044
10000064:	00000000 	nop
10000068:	3c040000 	lui	a0,0x0
1000006c:	34840000 	ori	a0,a0,0x0
10000070:	3c050000 	lui	a1,0x0
10000074:	34a50000 	ori	a1,a1,0x0
10000078:	3c1d0000 	lui	sp,0x0
1000007c:	37bdfff0 	ori	sp,sp,0xfff0
10000080:	10000003 	b	0x10000090
10000084:	00000000 	nop
10000088:	ac800000 	sw	zero,0(a0)
1000008c:	24840004 	addiu	a0,a0,4
10000090:	0085182a 	slt	v1,a0,a1
10000094:	1460fffc 	bnez	v1,0x10000088
10000098:	00000000 	nop
1000009c:	401a6000 	mfc0	k0,c0_sr
100000a0:	375affff 	ori	k0,k0,0xffff
100000a4:	409a6000 	mtc0	k0,c0_sr
100000a8:	00000000 	nop
100000ac:	0c0000ca 	jal	0x10000328          // jump to main
100000b0:	00000000 	nop
100000b4:	0800002d 	j	0x100000b4            // end here finally
100000b8:	27bdfff8 	addiu	sp,sp,-8      //
100000bc:	afbe0004 	sw	s8,4(sp)
100000c0:	03a0f025 	move	s8,sp
100000c4:	afc40008 	sw	a0,8(s8)
100000c8:	8fc20008 	lw	v0,8(s8)
100000cc:	00000000 	nop
100000d0:	8c420000 	lw	v0,0(v0)
100000d4:	03c0e825 	move	sp,s8
100000d8:	8fbe0004 	lw	s8,4(sp)
100000dc:	27bd0008 	addiu	sp,sp,8
100000e0:	03e00008 	jr	ra
100000e4:	00000000 	nop
100000e8:	27bdfff8 	addiu	sp,sp,-8      //
100000ec:	afbe0004 	sw	s8,4(sp)
100000f0:	03a0f025 	move	s8,sp
100000f4:	afc40008 	sw	a0,8(s8)
100000f8:	afc5000c 	sw	a1,12(s8)
100000fc:	8fc20008 	lw	v0,8(s8)
10000100:	8fc3000c 	lw	v1,12(s8)
10000104:	00000000 	nop
10000108:	ac430000 	sw	v1,0(v0)
1000010c:	00000000 	nop
10000110:	03c0e825 	move	sp,s8
10000114:	8fbe0004 	lw	s8,4(sp)
10000118:	27bd0008 	addiu	sp,sp,8
1000011c:	03e00008 	jr	ra
10000120:	00000000 	nop
10000124:	27bdfff8 	addiu	sp,sp,-8      //
10000128:	afbe0004 	sw	s8,4(sp)
1000012c:	03a0f025 	move	s8,sp
10000130:	afc40008 	sw	a0,8(s8)
10000134:	afc5000c 	sw	a1,12(s8)
10000138:	8fc20008 	lw	v0,8(s8)
1000013c:	00000000 	nop
10000140:	8c440000 	lw	a0,0(v0)
10000144:	8fc20008 	lw	v0,8(s8)
10000148:	8fc3000c 	lw	v1,12(s8)
1000014c:	00000000 	nop
10000150:	00831825 	or	v1,a0,v1
10000154:	ac430000 	sw	v1,0(v0)
10000158:	00000000 	nop
1000015c:	03c0e825 	move	sp,s8
10000160:	8fbe0004 	lw	s8,4(sp)
10000164:	27bd0008 	addiu	sp,sp,8
10000168:	03e00008 	jr	ra
1000016c:	00000000 	nop
10000170:	27bdfff8 	addiu	sp,sp,-8      //
10000174:	afbe0004 	sw	s8,4(sp)
10000178:	03a0f025 	move	s8,sp
1000017c:	afc40008 	sw	a0,8(s8)
10000180:	afc5000c 	sw	a1,12(s8)
10000184:	8fc20008 	lw	v0,8(s8)
10000188:	00000000 	nop
1000018c:	8c440000 	lw	a0,0(v0)
10000190:	8fc20008 	lw	v0,8(s8)
10000194:	8fc3000c 	lw	v1,12(s8)
10000198:	00000000 	nop
1000019c:	00831824 	and	v1,a0,v1
100001a0:	ac430000 	sw	v1,0(v0)
100001a4:	00000000 	nop
100001a8:	03c0e825 	move	sp,s8
100001ac:	8fbe0004 	lw	s8,4(sp)
100001b0:	27bd0008 	addiu	sp,sp,8
100001b4:	03e00008 	jr	ra
100001b8:	00000000 	nop
100001bc:	27bdfff8 	addiu	sp,sp,-8      //
100001c0:	afbe0004 	sw	s8,4(sp)
100001c4:	03a0f025 	move	s8,sp
100001c8:	afc40008 	sw	a0,8(s8)
100001cc:	afc5000c 	sw	a1,12(s8)
100001d0:	8fc20008 	lw	v0,8(s8)
100001d4:	00000000 	nop
100001d8:	8c430000 	lw	v1,0(v0)
100001dc:	8fc2000c 	lw	v0,12(s8)
100001e0:	00000000 	nop
100001e4:	00431006 	srlv	v0,v1,v0
100001e8:	30420001 	andi	v0,v0,0x1
100001ec:	03c0e825 	move	sp,s8
100001f0:	8fbe0004 	lw	s8,4(sp)
100001f4:	27bd0008 	addiu	sp,sp,8
100001f8:	03e00008 	jr	ra
100001fc:	00000000 	nop
10000200:	27bdffe8 	addiu	sp,sp,-24     //
10000204:	afbf0014 	sw	ra,20(sp)
10000208:	afbe0010 	sw	s8,16(sp)
1000020c:	03a0f025 	move	s8,sp
10000210:	afc40018 	sw	a0,24(s8)
10000214:	afc5001c 	sw	a1,28(s8)
10000218:	24030001 	li	v1,1
1000021c:	8fc2001c 	lw	v0,28(s8)
10000220:	00000000 	nop
10000224:	00431004 	sllv	v0,v1,v0
10000228:	00402825 	move	a1,v0
1000022c:	8fc40018 	lw	a0,24(s8)
10000230:	0c000049 	jal	0x10000124
10000234:	00000000 	nop
10000238:	00000000 	nop
1000023c:	03c0e825 	move	sp,s8
10000240:	8fbf0014 	lw	ra,20(sp)
10000244:	8fbe0010 	lw	s8,16(sp)
10000248:	27bd0018 	addiu	sp,sp,24
1000024c:	03e00008 	jr	ra
10000250:	00000000 	nop
10000254:	27bdffe8 	addiu	sp,sp,-24     //
10000258:	afbf0014 	sw	ra,20(sp)
1000025c:	afbe0010 	sw	s8,16(sp)
10000260:	03a0f025 	move	s8,sp
10000264:	afc40018 	sw	a0,24(s8)
10000268:	afc5001c 	sw	a1,28(s8)
1000026c:	24030001 	li	v1,1
10000270:	8fc2001c 	lw	v0,28(s8)
10000274:	00000000 	nop
10000278:	00431004 	sllv	v0,v1,v0
1000027c:	00021027 	nor	v0,zero,v0
10000280:	00402825 	move	a1,v0
10000284:	8fc40018 	lw	a0,24(s8)
10000288:	0c00005c 	jal	0x10000170
1000028c:	00000000 	nop
10000290:	00000000 	nop
10000294:	03c0e825 	move	sp,s8
10000298:	8fbf0014 	lw	ra,20(sp)
1000029c:	8fbe0010 	lw	s8,16(sp)
100002a0:	27bd0018 	addiu	sp,sp,24
100002a4:	03e00008 	jr	ra
100002a8:	00000000 	nop
100002ac:	27bdfff8 	addiu	sp,sp,-8          //
100002b0:	afbe0004 	sw	s8,4(sp)
100002b4:	03a0f025 	move	s8,sp
100002b8:	afc40008 	sw	a0,8(s8)
100002bc:	afc5000c 	sw	a1,12(s8)
100002c0:	8fc20008 	lw	v0,8(s8)
100002c4:	00000000 	nop
100002c8:	8c430000 	lw	v1,0(v0)
100002cc:	24040001 	li	a0,1
100002d0:	8fc2000c 	lw	v0,12(s8)
100002d4:	00000000 	nop
100002d8:	00441004 	sllv	v0,a0,v0
100002dc:	00402025 	move	a0,v0
100002e0:	8fc20008 	lw	v0,8(s8)
100002e4:	00641826 	xor	v1,v1,a0
100002e8:	ac430000 	sw	v1,0(v0)
100002ec:	00000000 	nop
100002f0:	03c0e825 	move	sp,s8
100002f4:	8fbe0004 	lw	s8,4(sp)
100002f8:	27bd0008 	addiu	sp,sp,8
100002fc:	03e00008 	jr	ra
10000300:	00000000 	nop
10000304:	27bdfff8 	addiu	sp,sp,-8          // user_interrupt
10000308:	afbe0004 	sw	s8,4(sp)
1000030c:	03a0f025 	move	s8,sp
10000310:	00000000 	nop
10000314:	03c0e825 	move	sp,s8
10000318:	8fbe0004 	lw	s8,4(sp)
1000031c:	27bd0008 	addiu	sp,sp,8
10000320:	03e00008 	jr	ra
10000324:	00000000 	nop
10000328:	27bdfff8 	addiu	sp,sp,-8      // main
1000032c:	afbe0004 	sw	s8,4(sp)
10000330:	03a0f025 	move	s8,sp
10000334:	1000ffff 	b	0x10000334        // while
10000338:	00000000 	nop
1000033c:	23bdff94 	addi	sp,sp,-108     // interrupt service routine
10000340:	afa10010 	sw	at,16(sp)
10000344:	afa20014 	sw	v0,20(sp)
10000348:	afa30018 	sw	v1,24(sp)
1000034c:	afa4001c 	sw	a0,28(sp)
10000350:	afa50020 	sw	a1,32(sp)
10000354:	afa60024 	sw	a2,36(sp)
10000358:	afa70028 	sw	a3,40(sp)
1000035c:	afa8002c 	sw	t0,44(sp)
10000360:	afa90030 	sw	t1,48(sp)
10000364:	afaa0034 	sw	t2,52(sp)
10000368:	afab0038 	sw	t3,56(sp)
1000036c:	afac003c 	sw	t4,60(sp)
10000370:	afad0040 	sw	t5,64(sp)
10000374:	afae0044 	sw	t6,68(sp)
10000378:	afaf0048 	sw	t7,72(sp)
1000037c:	afb8004c 	sw	t8,76(sp)
10000380:	afb90050 	sw	t9,80(sp)
10000384:	afbf0054 	sw	ra,84(sp)
10000388:	401a7000 	mfc0	k0,c0_epc
1000038c:	235afffc 	addi	k0,k0,-4
10000390:	afba0058 	sw	k0,88(sp)
10000394:	3c100100 	lui	s0,0x100
10000398:	36101ff8 	ori	s0,s0,0x1ff8
1000039c:	ae1a0000 	sw	k0,0(s0)
100003a0:	0000d810 	mfhi	k1
100003a4:	afbb005c 	sw	k1,92(sp)
100003a8:	0000d812 	mflo	k1
100003ac:	afbb0060 	sw	k1,96(sp)
100003b0:	afbe0064 	sw	s8,100(sp)
100003b4:	3c080100 	lui	t0,0x100
100003b8:	35081ff4 	ori	t0,t0,0x1ff4
100003bc:	8d090000 	lw	t1,0(t0)
100003c0:	21290001 	addi	t1,t1,1
100003c4:	ad090000 	sw	t1,0(t0)
100003c8:	00094880 	sll	t1,t1,0x2
100003cc:	01094022 	sub	t0,t0,t1
100003d0:	ad1d0000 	sw	sp,0(t0)
100003d4:	3c020100 	lui	v0,0x100
100003d8:	34421ffc 	ori	v0,v0,0x1ffc
100003dc:	24030001 	li	v1,1
100003e0:	ac430000 	sw	v1,0(v0)
100003e4:	0c0000c1 	jal	0x10000304          // jump to user_interrupt
100003e8:	00000000 	nop
100003ec:	23a50000 	addi	a1,sp,0
100003f0:	3c080100 	lui	t0,0x100
100003f4:	35081ff4 	ori	t0,t0,0x1ff4
100003f8:	8d090000 	lw	t1,0(t0)
100003fc:	2129ffff 	addi	t1,t1,-1
10000400:	ad090000 	sw	t1,0(t0)
10000404:	8fa10010 	lw	at,16(sp)
10000408:	8fa20014 	lw	v0,20(sp)
1000040c:	8fa30018 	lw	v1,24(sp)
10000410:	8fa4001c 	lw	a0,28(sp)
10000414:	8fa50020 	lw	a1,32(sp)
10000418:	8fa60024 	lw	a2,36(sp)
1000041c:	8fa70028 	lw	a3,40(sp)
10000420:	8fa8002c 	lw	t0,44(sp)
10000424:	8fa90030 	lw	t1,48(sp)
10000428:	8faa0034 	lw	t2,52(sp)
1000042c:	8fab0038 	lw	t3,56(sp)
10000430:	8fac003c 	lw	t4,60(sp)
10000434:	8fad0040 	lw	t5,64(sp)
10000438:	8fae0044 	lw	t6,68(sp)
1000043c:	8faf0048 	lw	t7,72(sp)
10000440:	8fb8004c 	lw	t8,76(sp)
10000444:	8fb90050 	lw	t9,80(sp)
10000448:	8fbf0054 	lw	ra,84(sp)
1000044c:	8fba0058 	lw	k0,88(sp)
10000450:	8fbb005c 	lw	k1,92(sp)
10000454:	03600011 	mthi	k1
10000458:	8fbb0060 	lw	k1,96(sp)
1000045c:	03600013 	mtlo	k1
10000460:	8fbe0064 	lw	s8,100(sp)
10000464:	23bd006c 	addi	sp,sp,108
10000468:	3c100100 	lui	s0,0x100
1000046c:	36101ffc 	ori	s0,s0,0x1ffc
10000470:	8e110000 	lw	s1,0(s0)
10000474:	2231ffff 	addi	s1,s1,-1
10000478:	03400008 	jr	k0
1000047c:	42000010 	c0	0x10
10000480:	00000000 	nop
10000484:	3c100100 	lui	s0,0x100
10000488:	36101ffc 	ori	s0,s0,0x1ffc
1000048c:	ae000000 	sw	zero,0(s0)
10000490:	08000002 	j	0x10000008
10000494:	00000000 	nop
