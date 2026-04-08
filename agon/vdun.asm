; void _vdun (unsigned char n, unsigned char ch, ...);

		.assume ADL=1

		xdef	__vdun

		section	code

__vdun:
        push    ix
        ld      ix,0
        add     ix,sp

        ld      a,(ix+6)
		or		a
		jr		z,@done
		ld		b,a
		lea		hl,(ix+9)
@loop:
		ld		a,(hl)
		inc		hl
		inc		hl
		inc		hl
		push	bc
		push	hl
		rst.lil	$10
		pop		hl
		pop		bc
		djnz	@loop
@done:
        pop     ix
        ret

