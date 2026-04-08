		.assume ADL=1

		xdef	__sext8

		section	code

; HL = sign-extend A to 24-bit
__sext8:
		ld		b, a
		rla
		sbc		hl, hl
		ld		l, b
		ret
