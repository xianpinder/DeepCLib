;
; void _vdus (const char *str);
;
		.assume	ADL=1

		xdef	__vdus

		section	code
__vdus:
		pop		de
		ex		(sp),hl
		push	de
		ld		bc,0
		xor		a
		rst.lil	$18
        ret
