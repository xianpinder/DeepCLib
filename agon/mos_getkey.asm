;
; int _mos_getkey (void);
;
		.assume	ADL=1

		xdef	__mos_getkey

		section	code
__mos_getkey:
        xor		a
		rst.lil	$8
		or		a
		sbc		hl,hl
		ld		l,a
        ret
