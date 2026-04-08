;
; int _mos_fopen (char *filename, int mode);
;
		.assume	ADL=1

		xdef	__mos_fopen

		section	code
__mos_fopen:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		ld		c,(ix+9)
        ld      a,$0A
		rst.lil	$8

		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
