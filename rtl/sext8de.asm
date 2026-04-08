		.assume ADL=1

		xdef	__sext8de

		section	code

; DE = sign-extend A to 24-bit
__sext8de:
		ex		de,hl
		ld		b, a
		rla
		sbc		hl, hl
		ld		l, b
		ex		de,hl
		ret
