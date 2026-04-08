;
; void _vduw (unsigned short val);
;
		.assume	ADL=1

		xdef	__vduw

		section	code
__vduw:
		pop		de
		ex		(sp),hl
		push	de
        ld      a,l
		rst.lil	$10
        ld      a,h
		rst.lil	$10
        ret
