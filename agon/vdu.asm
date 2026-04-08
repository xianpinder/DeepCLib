;
; void _vdu (const char ch);
;
		.assume	ADL=1

		xdef	__vdu

		section	code
__vdu:
		pop		de
		ex		(sp),hl
		push	de
        ld      a,l
		rst.lil	$10
        ret
