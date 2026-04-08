;
; int _mos_ren (char *src, char *dst);
;
		.assume	ADL=1

		xdef	__mos_ren

		section	code
__mos_ren:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		ld		de,(ix+9)
        ld      a,$06
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
