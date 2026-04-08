	.ASSUME ADL=1

	xdef __zext16
	xdef __sext16

	section code

__zext16:
    or		a
	jr		__ext16to24
__sext16:
	ld		a,h
	add		a,a
__ext16to24:
	push    de
    ex		de,hl
	sbc		hl,hl
    ld      h,d
    ld      l,e
    pop     de
	ret
