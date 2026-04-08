    .assume ADL=1

    xdef __not24
	xdef __not32

; AHL = ~AHL
__not32:
	cpl

; HL = ~HL
__not24:
	push	af
    ld      a,l
    cpl
    ld      l,a
    ld      a,h
    cpl
    ld      h,a
    ; Handle high byte
    push    hl
    ld      iy,0
    add     iy,sp
    ld      a,(iy+2)
    cpl
    ld      (iy+2),a
    pop     hl
	pop		af
    ret
