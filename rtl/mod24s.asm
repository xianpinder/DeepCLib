    .assume ADL=1

    xdef 	__mod24s
	xref	__div24u

; HL = HL % DE (signed, remainder has sign of dividend)
__mod24s:
    xor     a             ; Sign of quotient
    
    ; Make dividend positive (check bit 23)
    push    hl
    add     hl,hl           ; shift bit 23 into carry
    pop     hl
    jr      nc,@hl_pos
    inc     a
    push    de
    ex      de,hl
    or      a
    sbc		hl,hl
    sbc     hl,de			; HL = -HL
    pop     de
@hl_pos:
    
    ; Make divisor positive (check bit 23)
    push    de
    ex      de,hl
    add     hl,hl
    ex      de,hl
    pop     de
    jr      nc,@de_pos
    push    hl
    or      a,a
    sbc		hl,hl
    sbc     hl,de
    ex      de,hl			; DE = -DE
    pop     hl
@de_pos:

	push	af
    call    __div24u
    pop		af
	
	ex		de,hl			; HL = remainder

    ; Apply sign if needed
    rra
	ret		nc

	ex		de,hl
    or      a,a
    sbc		hl,hl
    sbc     hl,de			; HL = -HL
    ret
