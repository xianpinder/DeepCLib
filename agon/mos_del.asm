;
; int _mos_del (char *filename);
;
		.assume	ADL=1

		xdef	__mos_del

		section	code
__mos_del:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
        ld      a,$05
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
