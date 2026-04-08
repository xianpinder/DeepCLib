					assume	ADL=1

					xdef	__itof
					xref	__utof

					section	code

; convert a signed 24bit int in HL to a 24bit signed float in HL
; BC used as scratch register. Preserves A and DE
__itof:
					add		hl,de
					or		a
					sbc		hl,de
					ret		z						; int zero equals float zero

					push	hl
					pop		bc						; save HL in BC

					add		hl,hl					; move top bit of HL into carry
					jr		c,@isneg
					push	bc
					pop		hl						; restore original value to HL
					jp		__utof

@isneg:
; int is negative so convert it to positive
					or		a
					sbc		hl,hl
					sbc		hl,bc					; HL = 0 - BC

; convert the positive int to a float
					call	__utof

; set the float sign bit to negative
					;inc		l					; __utof clears bit 0 of L so can just increment it
					set		0,l
					ret
