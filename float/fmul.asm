					assume	ADL=1

					xdef	__fmul
					
					section	code

; __fmul : signed float HL = HL * DE
__fmul:
					ld		a,h
					or		l					; if HL == 0 then
					ret		z					; result will be zero so just return
					ld		a,d
					or		e					; if DE != 0 then
					jr		nz, @1				; need to do a multiply
					or		a					; else DE == 0 so result will be zero
					sbc		hl,hl				; so set HL = 0
					ret							; and return

; neither HL or DE are zero
@1:
					push	bc
					push	de

					ld		a,l
					xor		e
					and		$01					; A = sign of result
					push	af

					res		0,l					; HL = abs(HL)
					res		0,e					; DE = abs(DE)

					ld		b,h
					ld		c,l					; BC = HL
					
					ld		h,$00
					ld		l,h
					add		hl,de				; HLu = HLu + DEu (add the exponents)
					ex		de,hl				; DEu = final exponent
					push	de
;
; do HL = HL * BC
;
					ld		d,c
					ld		e,l
					mlt		de
					push	de     				; Push low product onto stack.
					ld		d,h      			; Prepare for high product
					ld		e,b
					ld		h,e      			; Swap bytes for 2 middle products. Do here when I have copies of high values
					ld		b,d      			; instead of later, needing A as temp.
					mlt		de      			; Calculate high product
					mlt		hl      			; Calculate first middle product
					mlt		bc      			; Calculate second middle product
					add.s	hl,bc   			; Sum middle products
					jr		nc,$+3
					inc		d       			; Inc D if carry.
					pop		bc      			; Retrieve low product.
					ld		a,b      			; Add in middle products to create final answer.
					add		a,l
					ld		b,a
					ld		a,e
					adc		a,h
					ld		e,a
					jr		nc,$+3
					inc		d

; Upper 16 bits in DE, lower 16 bits in BC

					pop		hl					; HLu = exponent
					ld		h,d
					ld		l,e					; HL = DE

					bit		7,h
					jr		nz,@isnorm				; already normalised so just return
					ld		a,h
					or		l
					jr		nz,@notzero				; only normalise if not zero
					sbc		hl,hl					; make sure uHL is also zero
					jr		@isnorm
@notzero:
					ld		bc,$FF0000
@normloop:
					add		hl,bc					; HLu = HLu - 1
					sla		l
					rl		h						; HL16 = HL16 << 1
					jp		p,@normloop
@isnorm:
					
					pop		af
					res		0,l						; clear sign bit					
					or		l
					ld		l,a

					pop		de
					pop		bc
					ret
