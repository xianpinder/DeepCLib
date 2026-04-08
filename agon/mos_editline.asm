;
; int _mos_editline (char *buf, int size, int flags);
;
		.assume	ADL=1

		xdef	__mos_editline

		section	code
__mos_editline:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		ld		bc,(ix+9)
		ld		e,(ix+12)
        ld      a,$09
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
