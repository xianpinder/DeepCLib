    .assume ADL=1

    xdef __cmp32s

;------------------------------------------------------------
; __cmp32s - Signed 32-bit comparison
; Input: AHL, CDE = values to compare
; Output: Flags set as if AHL - CDE
;         Z=1 if equal, C=1 if AHL < CDE (signed)
; Preserves: all registers
;------------------------------------------------------------
__cmp32s:
    push    bc
    push    hl
    ld      iyl,a           ; Save A

    add     a,$80
    ld      b,a
    ld      a,c
    add     a,$80
    ld      c,a
    ld      a,b
    cp      c
    jr      nz,@done

    sbc     hl,de
@done:
    pop     hl
    pop     bc
    ld      a,iyl           ; Restore A without affecting flags
    ret