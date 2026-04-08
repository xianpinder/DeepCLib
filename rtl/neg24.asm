    .assume ADL=1

    xdef __neg24

; HL = -HL

__neg24:
    push    de
    ex      de,hl
    or      a,a             ; Clear carry
    sbc		hl,hl			; HL = 0
    sbc     hl,de			; HL = 0 - DE
    pop     de
    ret
