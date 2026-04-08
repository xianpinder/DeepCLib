;
; int _mos_fread (int fhandle, void *buffer, size_t nbytes);
;
		.assume	ADL=1

		xdef	__mos_fread

		section	code
__mos_fread:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		c,(ix+6)
		ld		hl,(ix+9)
		ld		de,(ix+12)
        ld      a,$1A
		rst.lil	$8
		ex 		de,hl

		pop		ix
        ret
