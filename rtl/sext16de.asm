	.ASSUME ADL=1

	xdef __sext16de

	section code

__sext16de:
	push    hl
	ld		a,d
	add		a,a
	sbc		hl,hl
    ld      h,d
    ld      l,e
    ex		de,hl
    pop     hl
	ret
