;
; void *_mos_getfil (int fhandle);
;
		.assume	ADL=1

		xdef	__mos_getfil

		section	code
__mos_getfil:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		c,(ix+6)
        ld      a,$19
		rst.lil	$8

		pop		ix
        ret
