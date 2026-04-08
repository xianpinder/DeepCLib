;
; int _mos_oscli (char *command);
;
		.assume	ADL=1

		xdef	__mos_oscli

		section	code
__mos_oscli:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
        ld      a,$10
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
