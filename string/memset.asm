		assume	ADL=1
		
		xdef	_memset
		xref	__ac_memset
		
		section	code
_memset:
		ld		iy,0
		add		iy,sp
		ld		hl,(iy+3)
		ld		de,(iy+6)
		ld		bc,(iy+9)
		push	hl
		call	__ac_memset
		pop		hl
		ret