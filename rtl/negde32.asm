    .assume ADL=1

    xdef __negde32

; CDE = -CDE
__negde32:
	push	af
    push    hl
    xor     a             	; A = 0 and clear carry
    sbc		hl,hl			; HL = 0
    sbc     hl,de			; HL = 0 - DE
	sbc		a,c				; AHL = 0 - CDE
    ex      de,hl
	ld		c,a				; CDE = AHL
    pop     hl
	pop		af
    ret
