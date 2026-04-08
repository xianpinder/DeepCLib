    .assume ADL=1

    xdef __or24
	xdef __or32

; AHL = AHL | CDE
__or32:
	or		c

; HL = HL | DE
__or24:
	push	af
    ld      a,l
    or      e
    ld      l,a
    ld      a,h
    or      d
    ld      h,a
    ; Handle high byte
    push    hl
    push    de
    ld      iy,0
    add     iy,sp
    ld      a,(iy+2)
    or      (iy+5)
    ld      (iy+5),a
    pop     de
    pop     hl
	pop		af
    ret
