;
; int _mos_flseek_p (int fhandle, void *fil);
;
		.assume	ADL=1

		xdef	__mos_flseek_p

		section	code
__mos_flseek_p:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		c,(ix+6)
		ld		hl,(ix+9)
        ld      a,$24
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
