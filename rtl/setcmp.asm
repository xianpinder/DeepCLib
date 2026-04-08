    .assume ADL=1

    xdef	__setgtu
    xdef	__setgts
    xdef	__setleu
    xdef	__setles

;============================================================================
; Set comparison result helpers
;============================================================================

; Set HL=1 if previous compare showed greater-than (unsigned)
__setgtu:
    ld      hl,0
    ret     z               ; Equal, not greater
    ret     c               ; Less than, not greater
    inc     l
    ret

; Set HL=1 if greater-than (signed)
__setgts:
    ld      hl,0
    ret     z
	ret		m
    inc     l
    ret

; Set HL=1 if less-or-equal (unsigned)
__setleu:
    ld      hl,1
    ret     z               ; Equal
    ret     c               ; Less than
    dec     l               ; Greater than
    ret

; Set HL=1 if less-or-equal (signed)
__setles:
    ld      hl,1
    ret     z
	ret		m
    dec     l
    ret
