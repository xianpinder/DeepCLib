    .assume ADL=1

	xdef	__lnot24

; HL = !HL
__lnot24:
	add		hl,de
	or		a
	sbc		hl,de 
	inc		hl			; if HL == 0 then HL = 1
	ret		z			; return if HL was 0
	or		a			; HL wasn't zero
	sbc		hl,hl		; so set it to zero
	ret
