	assume	ADL=1

	xdef	__mod32u
	xdef	__mod32s
	xref	__div32u
	xref	__div32s

	section code

; AHL = AHL % CDE (unsigned)
__mod32u:
    call    __div32u
    ld      a,c
    ex      de,hl
    ret

; AHL = AHL % CDE (signed)
__mod32s:
    call    __div32s
    ld      a,c
    ex      de,hl
    ret