    .assume ADL=1

    xdef	__mul24s
	xref	__mul24

; HL = HL * DE (signed)
; Handle signs, then use unsigned multiply

__mul24s:
    xor		a             ; Sign flag
    
    ; Check if HL is negative (bit 23 into carry)
    push    hl
    add     hl,hl
    pop     hl
    jr      nc,@hl_pos
    inc     a               ; Toggle sign
    push    de
	ex      de,hl
    or      a,a
    sbc		hl,hl
    sbc     hl,de			; HL = -HL
    pop     de
@hl_pos:
    
    ; Check if DE is negative (bit 23 into carry)
    push    de
    ex      de,hl
    add     hl,hl
    ex      de,hl
    pop     de
    jr      nc,@de_pos
    inc     a
    push    hl
    or      a,a
    sbc		hl,hl
    sbc     hl,de
    ex      de,hl			; DE = -DE
    pop     hl
@de_pos:
    
    ; Do unsigned multiply
	push	af
    call    __mul24
	pop		af
    
    ; Apply sign if needed
    rra
	ret		nc

    push    de
    ex      de,hl
    or      a,a
    sbc		hl,hl
    sbc     hl,de			; HL = -HL
    pop     de
    ret
