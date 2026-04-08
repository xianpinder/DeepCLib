;
; void _fabs (double d);
;
		.assume	ADL=1

		xdef	_fabs
		xdef	_fabsf

		section	code
_fabsf:
_fabs:
		pop		de
		ex		(sp),hl
		push	de
		res		0,l
        ret
