    .assume ADL=1

    xdef __and24
	xdef __and32

; AHL = AHL & CDE
__and32:
	and		c

; HL = HL & DE
__and24:
	push	af
    ld      a,l
    and     e
    ld      l,a
    ld      a,h
    and     d
    ld      h,a
    ; Handle high byte (bits 16-23)
    push    hl
    push    de
    ld      iy,0
    add     iy,sp
    ld      a,(iy+2)	; High byte of DE
    and     (iy+5)		; High byte of HL
    ld      (iy+5),a
    pop     de
    pop     hl
	pop		af
    ret
