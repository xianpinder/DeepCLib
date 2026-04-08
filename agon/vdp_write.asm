;
; void _vdp_write (void *data, size_t nbytes);
;
		.assume	ADL=1
		xdef	__vdp_write

		section	code
__vdp_write:
        push    ix
        ld      ix,0
        add     ix,sp

        ld      hl,(ix+6)
		ld		bc,(ix+9)

		add		hl,de
		or		a
		sbc		hl,de
		jr		z,@done

		xor		a
		rst.lil	$18
@done:
        pop     ix
        ret
