;
; int _ffs_fsize (void *fil, void *size);
;
		.assume	ADL=1

		xdef	__ffs_fsize

		section	code
__ffs_fsize:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		push	hl
        ld      a,$86
		rst.lil	$8
		pop		hl
	
		ld		de,(ix+9)
        ld      a,$8F
		rst.lil	$8
		
		or		a
		sbc		hl,hl
		ld		l,a

		pop		ix
        ret
