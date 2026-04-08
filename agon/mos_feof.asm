;
; int _mos_feof (int fhandle);
;
		.assume	ADL=1

		xdef	__mos_feof

		section	code
__mos_feof:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		c,(ix+6)
        ld      a,$0E
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
