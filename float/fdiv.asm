					assume	ADL=1
					xdef	__fdiv
					
					section	code

; __fdiv: signed float HL = HL / DE
__fdiv:
					ld		a,h
					or		l					; if HL == 0 then
					ret		z					; result will be zero so just return

					ld		a,d
					or		e					; if DE != 0 then
					jr		nz, @notzero		; need to do a divide 
					ld		hl,$7FFFE			; else DE == 0 so result will be INF, so set HL = $7FFFE
					ret							; and return
@notzero:
					push	ix
					push	bc
					push	de

					ld		a,l
					xor		e
					and		$01					; A = sign of result
					res		0,l					; HL = abs(HL)
					res		0,e					; DE = abs(DE)
					push	af
					call	@fltdivu			; HL = HL / DE
					pop		af
					or		l
					ld		l,a

					pop		de
					pop		bc
					pop		ix
					ret

; fltdivu: float HL = HL / DE
; HL and DE must be normalised
; assumes HL and DE are both positive
;
@fltdivu:
					ld		a,h
					ld		c,l					; AC = HL
					ld		ix,$000000			; IX = 0

					push	de					; save DE
					ld		d,$00
					ld		e,d
					or		a
					sbc		hl,de				; HLu = HLu - DEu (subtract the exponents)
					pop		de
					push	hl					; HLu = final exponent

; do ACIX = ACIX / DE

					or		a
					sbc		hl,hl				; HL = 0
					ld		b,32
@loop:
					add.s	ix,ix
					rl		c
					rla							
					adc.s	hl,hl				; HLACIX = HLACIX << 1
					jr		c,@overflow
					sbc.s	hl,de				; HL = HL - DE
					jr		nc,@setbit
					add.s	hl,de
					djnz	@loop
					jr		@divdone
@overflow:
					or		a
					sbc.s	hl,de
@setbit:
					inc		ixl
					djnz	@loop
@divdone:
					pop		de					; DEu = exponent
					ld		d,ixh
					ld		e,ixl				; DE = IX
					ex		de,hl				; HL = DE

					rr		c
					jr		nc,@notbig
					rr		h
					rr		l
					ld		de,$010000
					add		hl,de
@notbig:
					call	fltnormu
					res		0,l					; clear sign bit					
					
					ret

;============================================================================================================

; fltnormu: adjust unsigned float (HL*2^HLu) so that top bit of HL is set
fltnormu:
					bit		7,h
					ret		nz						; already normalised so just return
					ld		a,h
					or		l
					jr		nz,@notzero				; only normalise if not zero
					sbc		hl,hl					; make sure uHL is also zero
					ret
@notzero:
					push	de
					ld		de,$FF0000
@nloop:
					sla		l
					rl		h						; HL16 = HL16 << 1
					add		hl,de					; HLu = HLu - 1
					bit		7,h
					jr		z,@nloop
					pop		de
					ret