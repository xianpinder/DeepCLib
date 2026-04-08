    .assume ADL=1

    xdef 	__zext8

; HL = zero-extend A to 24-bit
__zext8:
    or      a           ; Clear carry
    sbc     hl,hl       ; HL = 0
    ld      l,a         ; L = 8-bit value
    ret
