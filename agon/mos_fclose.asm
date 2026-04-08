;
; int _mos_fclose (int fhandle);
;
		.assume	ADL=1

		xdef	__mos_fclose

		section	code
__mos_fclose:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		c,(ix+6)
        ld      a,$0B
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
