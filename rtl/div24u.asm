    .assume ADL=1

    xdef __div24u

; HL = HL / DE, DE = HL % DE (unsigned)

__div24u:
    push    bc
    
    push    de
    pop     bc              ; BC = divisor
    ex      de,hl           ; DE = dividend
	or		a
    sbc		hl,hl			; HL = remainder
    
    ld      a,24            ; 24 bits
@loop:
    ex      de,hl
    add     hl,hl			; Shift DE left, MSB into carry
    ex      de,hl
    adc     hl,hl			; Shift carry into remainder
    
    or      a,a             ; Clear carry
    sbc     hl,bc			; Try to subtract divisor
    jr      nc,@fits
    add     hl,bc			; Doesn't fit, restore remainder
    jr      @next
@fits:
    inc     de				; Fits, set bit in quotient
@next:
    dec     a
    jr      nz,@loop
    
    ex      de,hl			; HL = quotient, DE = remainder
    pop     bc
    ret
