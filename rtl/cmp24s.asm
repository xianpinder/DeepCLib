    .assume ADL=1

    xdef __cmp24s

;------------------------------------------------------------
; __cmp24s - Signed 24-bit comparison
; Input: HL, DE = values to compare
; Output: Flags set as if HL - DE
;         Z=1 if equal, C=1 if HL < DE (signed)
; Preserves: HL, DE
;------------------------------------------------------------
__cmp24s:
    push    hl
    push    de
    push    bc
    
    ; Add 0x800000 to both values to convert signed to unsigned order
    ld      bc,0x800000
    add     hl,bc
    ex      de,hl
    add     hl,bc
    ex      de,hl
    
    ; Unsigned compare
    or      a             	; Clear carry
    sbc     hl,de           ; C=1 if HL < DE, Z=1 if equal
    
    pop     bc
    pop     de
    pop     hl
    ret
