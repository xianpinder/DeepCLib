					assume	ADL=1

					xdef	__fadd
					xdef	__fsub
					
					section	code

; __fadd: signed float HL = HL + DE
__fadd:
					push	bc
					push	de
					ld		a,l
					and		$01
					ld		b,a					; B = sign of HL
					xor		e

					res		0,l					; HL = abs(HL)
					res		0,e					; DE = abs(DE)

					bit		0,a
					jr		z, @1
;
; signs are different so need to subtract
;
					call	fltsubu
					xor		b
					or		l
					ld		l,a

					ld		a,h
					or		a
					jr		nz,@notzero
					ld		l,h
@notzero:
					pop		de
					pop		bc
					ret			
;
; signs are the same so need to add
;
@1:
					call	fltaddu
					ld		a,l
					or		b
					ld		l,a
					pop		de
					pop		bc
					ret

;============================================================================================================

; fltsub: signed float HL = HL - DE
__fsub:
					push	bc
					push	de
					ld		a,l
					and		$01
					ld		b,a					; B = sign of HL
					xor		e

					res		0,l					; HL = abs(HL)
					res		0,e					; DE = abs(DE)

					bit		0,a
					jr		z, @1
;
; signs are different so need to add
;
					call	fltaddu
					ld		a,l
					or		b
					ld		l,a
					pop		de
					pop		bc
					ret
;
; signs are the same so need to subtract
;
@1:
					call	fltsubu
					xor		b
					or		l
					ld		l,a

					ld		a,h
					or		a
					jr		nz,@notzero
					ld		l,h
@notzero:

					pop		de
					pop		bc
					ret

;============================================================================================================

; fltaddu : float HL = HL + DE
; assumes HL and DE are both positive
fltaddu:
					ld		a,d
					or		e
					ret		z					; return if DE = 0
					
					ld		a,h
					or		l
					jr		nz,@notzero
					ex		de,hl				; HL = 0 so return DE
					ret
@notzero:
					push	bc					; Save BC so we don't corrupt it

					dec		sp
					push	hl
					push	de
					inc		sp
					pop		af					; A = DEu
					pop		bc					; B = HLu

					sub		b					; A = DEu - HLu
					jr		z,@dofltaddu		; if exponents are equal then do the addition
					jp		p,@adjfltaddu
					ex		de,hl
					neg
@adjfltaddu:
					ld		b,a
@afauloop:
					srl		h
					rr		l
					djnz	@afauloop
					

; when we get to here the exponents are the same
; do a 16bit add HL = HL + DE
@dofltaddu:
					add.s	hl,de
					ld		d,h
					ld		e,l
					ex		de,hl
					jr		nc,@nofaov
;
; the addition overflowed so rotate the carry back in
; and increase the exponent
;
					rr		h
					rr		l
					ld		bc,$010000
					add		hl,bc
@nofaov:
					res		0,l					; clear the sign bit
					pop 	bc
					ret

;============================================================================================================
;
; fltsubu: float HL = HL - DE
; assumes HL and DE are both positive
; on return A = sign of result (00 = positive, 01 = negative)
;
fltsubu:
					ld		a,d
					or		e
					ret		z					; return if DE = 0
					
					ld		a,h
					or		l
					jr		nz,@notzero
					ex		de,hl				; if HL = 0 then return -DE
					inc		a
					ret
@notzero:
					push	bc					; Save BC so we don't corrupt it

					dec		sp
					push	hl
					push	de
					inc		sp
					pop		af					; A = DEu
					pop		bc					; B = HLu

					sub		b					; A = DEu - HLu
					jr		z,dofltsubu			; if exponents are equal then do the addition
					jp		p,adjfltsubu

; increase exponent of DE until it matches HL
					push	hl
					neg
					ld		b,a
@1:
					srl		d					; DE >> 1
					rr		e
					djnz	@1

					ld		h,d
					ld		l,e
					ex		de,hl
					pop		hl
					jr		dofltsubu

; increase exponent of HL until it matches DE
adjfltsubu:
					ld		b,a
@2:
					srl		h					; HL >> 1
					rr		l
					djnz	@2

; exponents are the same, do the subtraction
dofltsubu:

					xor		a
					ld		b,a					; b (sign) = 0 (positive)
					sbc.s	hl,de

					jr		nc,afsupos			; if result positive no need to negate

					inc		b					; b (sign) = 01 (negative)
					
					xor		a
					sub		l
					ld		l,a
					sbc		a,a
					sub		h
					ld		h,a					; HL = -HL
afsupos:
					ld		d,h					; DEu contains exponent
					ld		e,l					; so copy it across to HL
					ex		de,hl

					bit		7,h
					jr		nz,@isnorm			; already normalised so just return
					ld		a,h
					or		l
					jr		nz,@notzero			; only normalise if not zero
					sbc		hl,hl				; make sure uHL is also zero
					jr		@isnorm
@notzero:
					ld		de,$FF0000
@normloop:
					add		hl,de				; HLu = HLu - 1
					sla		l
					rl		h					; HL16 = HL16 << 1
					jp		p,@normloop
					;bit		7,h
					;jr		z,@normloop
@isnorm:
					res		0,l					; clear the sign bit
					
					ld		a,b					; A = sign of result
					pop		bc
					ret

;============================================================================================================


