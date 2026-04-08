    .assume ADL=1

    xdef __xor24
	xdef __xor32

; AHL = AHL ^ CDE
__xor32:
	xor		c

; HL = HL ^ DE
__xor24:
	push	af
    ld      a,l
    xor     e
    ld      l,a
    ld      a,h
    xor     d
    ld      h,a
    ; Handle high byte
    push    hl
    push    de
    ld      iy,0
    add     iy,sp
    ld      a,(iy+2)
    xor     (iy+5)
    ld      (iy+5),a
    pop     de
    pop     hl
	pop		af
    ret