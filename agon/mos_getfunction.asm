;
; void *_mos_getfunction (int fn);
;
		.assume	ADL=1

		xdef	__mos_getfunction

		section	code
__mos_getfunction:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		b,(ix+6)
		ld		c,0
        ld      a,$50
		rst.lil	$8
		pop		ix
		
		or		a
		ret		z
		sbc		hl,hl
        ret
