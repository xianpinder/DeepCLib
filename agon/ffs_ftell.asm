;
; int _ffs_ftell (void *fil, void *pos);
;
		.assume	ADL=1

		xdef	__ffs_ftell

		section	code
__ffs_ftell:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		ld		de,(ix+9)
        ld      a,$8D
		rst.lil	$8
		
		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
