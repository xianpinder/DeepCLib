    .assume ADL=1

    xdef __shr24u

; HL = (unsigned) HL >> DE 

__shr24u:
	ld		a,e
    or      a
    ret     z

    push    hl
    ld      iy,0
    add     iy,sp
@loop:
    srl     (iy+2)		; High byte
    rr      (iy+1)		; Middle byte
    rr      (iy+0)		; Low byte
	dec		a
    jr    	nz,@loop
    pop     hl
    ret
