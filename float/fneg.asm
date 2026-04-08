					assume	ADL=1

					xdef	__fneg
					
					section	code
; __fneg: HL = -HL
__fneg:
					ld		a,l
					or		h
					ret		z					; can't negate zero so return
					
					ld		a,l
					xor		$01					; flip bit 0 of HL
					ld		l,a
					ret