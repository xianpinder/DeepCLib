;
; double copysign(double x, double y);
;
		.assume	ADL=1

		xdef	_copysign
		xdef	_copysignf

		section	code

_copysign:
_copysignf:
		ld		hl, 3
		add		hl, sp
		ld		de, (hl)
		inc		hl
		inc		hl
		inc		hl
		ld		hl, (hl)
		ex		de,hl

		ld		a,l
		or		h
		ret		z
	
		rr		l
		rr		e
		rl		l
        ret
