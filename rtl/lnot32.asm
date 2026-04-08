    .assume ADL=1

	xdef	__lnot32

; AHL = !AHL
__lnot32:
	or		a
	jr		z,@chkzero	; AHL might be zero so need to check further
	xor		a			; AHL not zero
	sbc		hl,hl		; so set HL to zero
	ret
	
@chkzero:
	add		hl,de
	or		a
	sbc		hl,de 
	inc		hl			; if HL == 0 then HL = 1
	ret		z			; return if HL was 0
	or		a			; HL wasn't zero
	sbc		hl,hl		; so set it to zero
	ret
