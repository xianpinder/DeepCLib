; char *strcpy (char *s1, const char *s2)

			assume	ADL=1
			xdef	_strcpy
			xdef	__ac_strcpy
			
			section	code

_strcpy:
			pop		bc
			pop		hl
			pop		de
			push	de
			push	hl
			push	bc
__ac_strcpy:		
			push	hl
			pop		bc
@loop:
			ld		a,(de)
			ld		(bc),a
			or		a
			ret		z
			inc		de
			inc		bc
			jr		@loop
