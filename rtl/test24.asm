    .assume ADL=1

    xdef	__test24

; Set Z flag if HL == 0
__test24:
    add     hl,de       ; HL = HL + DE
    or      a         	; Clear carry
    sbc     hl,de       ; HL = HL + DE - DE = original HL, Z set if HL == 0
    ret
