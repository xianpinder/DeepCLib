					assume	ADL=1

					xdef	__ftoi
					xref	__ftou
					
					section	code
; HL = int(HL)
__ftoi:
					bit		0,l
					jp		z, __ftou

; float is negative
					res		0,l
					call	__ftou
					push	de
					ex		de,hl
					or		a
					sbc		hl,hl
					sbc		hl,de
					pop		de
					ret