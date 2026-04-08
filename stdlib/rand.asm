; 16-bit xorshift pseudorandom number generator
; code by John Metcalf
; returns   HL = pseudorandom number (0..65534)

		.assume	ADL=1

		xdef	_rand
		xdef	_srand

_rand:
		ld		hl,(rand_seed)
		ld		a,h
		rra
		ld		a,l
		rra
		xor		h
		ld		h,a
		ld		a,l
		rra
		ld		a,h
		rra
		xor		l
		ld		l,a
		xor		h
		ld		h,a
		ld		(rand_seed),hl
		dec		hl
		ret

_srand:
		pop		de
		ex		(sp),hl
		push	de
		ld		a,l
		or		h
		jr		nz,@set
		inc		hl
@set:
		ld		(rand_seed),hl
		ret

rand_seed:		dl	1
