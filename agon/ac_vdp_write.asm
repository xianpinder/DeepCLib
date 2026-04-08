;
; __asmcall void _vdp_write (void *data, size_t nbytes);
;
		.assume	ADL=1
		xdef	__ac_vdp_write

		section	code
__ac_vdp_write:
		push	de
		pop		bc			; BC = nbytes
		xor		a

		rst.lil	$18
        ret
