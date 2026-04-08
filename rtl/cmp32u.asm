    .assume ADL=1

    xdef	__cmp32u

__cmp32u:
	cp		c
	ret		nz
	push	hl
    or      a
    sbc     hl,de
	pop		hl
    ret