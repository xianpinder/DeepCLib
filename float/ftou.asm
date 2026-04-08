					assume	ADL=1

					xdef	__ftou
					
					section	code

; convert a 24 bit positive float in HL to 24 bit unsigned int in HL
__ftou:
					push	bc
					push	de
					ex		de,hl				; DE = HL
					or		a
					sbc		hl,hl				; HL = 0

					dec		sp
					push	de
					inc		sp
					pop		bc					; B = exponent (DEu)

					bit		7,b
					jr		nz,@return			; exponent is negative so value is < 1.0
					ld		a,b
					or		a
					jr		z,@return			; exponent is 0 so value is < 1.0

					cp		25
					jr		nc,@overflow

					ld		h,d
					ld		l,e					; HL = mantissa

					cp		16
					jr		z,@return			; no shifting needed
					jr		nc,@shiftleft

					ld		a,16
					sub		b
					ld		b,a
@loop:
					srl		h					; HL >> 1
					rr		l
					djnz	@loop
					jr		@return
@shiftleft:
					sub		16
					ld		b,a
@left:
					add		hl,hl
					djnz	@left
@return:
					pop		de
					pop		bc
					ret
@overflow:
					dec		hl
					jr		@return
