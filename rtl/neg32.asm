    .assume ADL=1

    xdef __neg32

; AHL = -AHL
__neg32:
	push	bc
    push    de
    ex      de,hl
	ld		c,a				; CDE = AHL
    xor     a             	; A = 0 and clear carry
    sbc		hl,hl			; HL = 0
    sbc     hl,de			; HL = 0 - DE
	sbc		a,c				; AHL = 0 - CDE
    pop     de
	pop		bc
    ret
