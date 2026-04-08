    .assume ADL=1

    xdef	__mod24u
	xref	__div24u

; HL = HL % DE (unsigned)

__mod24u:
    call    __div24u
    ex      de,hl           ; Return remainder in HL
    ret

