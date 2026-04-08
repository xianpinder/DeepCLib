    .assume ADL=1

    xdef __shr32s

; AHL = (signed) AHL >> E

__shr32s:
	inc		e
	dec		e
	ret		z

    push    hl
    ld      iy,0
    add     iy,sp
@loop:
	sra		a
    rr      (iy+2)		; High byte
    rr      (iy+1)		; Middle byte
    rr      (iy+0)		; Low byte
	dec		e
    jr		nz,@loop
    pop     hl
    ret