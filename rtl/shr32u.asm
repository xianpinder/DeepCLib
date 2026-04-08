    .assume ADL=1

    xdef __shr32u

; AHL = (unsigned) AHL >> E 

__shr32u:
	inc		e
	dec		e
	ret		z

    push    hl
    ld      iy,0
    add     iy,sp
@loop:
	srl		a
    rr      (iy+2)		; High byte
    rr      (iy+1)		; Middle byte
    rr      (iy+0)		; Low byte
	dec		e
    jr		nz,@loop
    pop     hl
    ret
