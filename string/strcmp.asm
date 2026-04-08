; int strcmp (char 7*s1, char *s2)
; __asmcall int _ac_strcmp (char *s1, char *s2)

		assume 	ADL=1

		xdef	__ac_strcmp
		xdef	_strcmp

		section	code

_strcmp:
		pop		bc
		pop		hl
		pop		de
		push	de
		push	hl
		push	bc

__ac_strcmp:
		ex		de,hl
@loop:
		ld		a, (de)
		or		a
		jr		z, @done
		cpi
		inc		de
		jr		z, @loop
		dec		hl
@done:
		sub		(hl)

		ld		d, a
		rla
		sbc		hl, hl
		ld		l, d
		ret