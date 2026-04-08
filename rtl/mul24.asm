    .assume ADL=1

    xdef __mul24

; HL = HL * DE (unsigned)
; Uses shift-and-add algorithm

__mul24:
    push    bc
    push    de
    
    push    hl
    pop     bc              ; BC = HL (multiplier)
	or		a
    sbc		hl,hl			; HL = result accumulator
    
    ld      a,24            ; 24 bits to process
@loop:
    add     hl,hl           ; Shift result left
    ex      de,hl
    add     hl,hl           ; Shift DE (multiplicand bits) left
    ex      de,hl
    jr      nc,@skip 		; If high bit of DE wasn't set, skip add
    add     hl,bc           ; Add multiplier to result
@skip:
    dec     a
    jr      nz,@loop
    
    pop     de
    pop     bc
    ret
