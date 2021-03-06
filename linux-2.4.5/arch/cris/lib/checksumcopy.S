/* $Id: checksumcopy.S,v 1.4 2001/02/19 11:11:34 bjornw Exp $
 * A fast checksum+copy routine using movem
 * Copyright (c) 1998, 2001 Axis Communications AB
 *
 * Authors:	Bjorn Wesen
 * 
 * csum_partial_copy_nocheck(const char *src, char *dst,
 *		             int len, unsigned int sum)
 */

	.globl	_csum_partial_copy_nocheck
_csum_partial_copy_nocheck:	
	
	;; r10 - src
	;; r11 - dst
	;; r12 - length
	;; r13 - checksum

	;; check for breakeven length between movem and normal word looping versions
	
	cmpu.w	80,r12
	blo	word_loop
	nop

	;; need to save the registers we use below in the movem loop
	;; this overhead is why we have a check above for breakeven length
	
	subq	9*4,sp
	movem	r8,[sp]
	
	;; do a movem copy and checksum

	subq	10*4,r12	; update length for the first loop
	
mloop:	movem	[r10+],r9	; read 10 longwords
	movem	r9,[r11+]	; write 10 longwords

	;; perform dword checksumming on the 10 longwords
	
	add.d	r0,r13
	ax
	add.d	r1,r13
	ax
	add.d	r2,r13
	ax
	add.d	r3,r13
	ax
	add.d	r4,r13
	ax
	add.d	r5,r13
	ax
	add.d	r6,r13
	ax
	add.d	r7,r13
	ax
	add.d	r8,r13
	ax
	add.d	r9,r13

	;; fold the carry into the checksum, to avoid having to loop the carry
	;; back into the top
	
	ax
	addq	0,r13
	ax			; do it again, since we might have generated a carry
	addq	0,r13

	subq	10*4,r12
	bge	mloop
	nop

	addq	10*4,r12	; compensate for last loop underflowing length

	movem	[sp+],r8	; restore regs

word_loop:
	;; only fold if there is anything to fold.

	cmpq	0,r13
	beq	no_fold

	;; fold 32-bit checksum into a 16-bit checksum, to avoid carries below
	;; r9 can be used as temporary.
	
	move.d	r13,r9
	lsrq	16,r9		; r0 = checksum >> 16
	and.d	0xffff,r13	; checksum = checksum & 0xffff
	add.d	r9,r13		; checksum += r0
	move.d	r13,r9		; do the same again, maybe we got a carry last add
	lsrq	16,r9
	and.d	0xffff,r13
	add.d	r9,r13
	
no_fold:
	cmpq	2,r12
	blt	no_words
	nop
	
	;; copy and checksum the rest of the words
	
	subq	2,r12
	
wloop:	move.w	[r10+],r9
	addu.w	r9,r13
	subq	2,r12
	bge	wloop
	move.w	r9,[r11+]
	
	addq	2,r12
		
no_words:
	;; see if we have one odd byte more
	cmpq	1,r12
	beq	do_byte
	nop
	ret
	move.d	r13, r10

do_byte:	
	;; copy and checksum the last byte
	move.b	[r10],r9
	addu.b	r9,r13
	move.b	r9,[r11]
	ret
	move.d	r13, r10
		
	
