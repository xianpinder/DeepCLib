    .assume ADL=1

    xdef	__cmp24u

;------------------------------------------------------------
; __cmp24u - Unsigned 24-bit comparison
; Input: HL, DE = values to compare
; Output: Flags set as if HL - DE
;         Z=1 if equal, C=1 if HL < DE (unsigned)
; Preserves: HL, DE
;------------------------------------------------------------
__cmp24u:
	push	hl
    or      a             	; Clear carry
    sbc     hl,de           ; Sets Z, S flags
	pop		hl
    ret