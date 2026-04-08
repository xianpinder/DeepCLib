; void *calloc(size_t nelem, size_t elsize)

	assume ADL=1

	xdef	_calloc

	xref	_malloc
	xref	__ac_memset
	xref	__mul24

	section code

_calloc:
	ld		iy,0
	add		iy,sp

	ld		hl,(iy+3)		; HL = nelem
	ld		de,(iy+6)		; DE = elsize
	call	__mul24			; HL = nelem * elsize
	push	hl				; save size

	push	hl
	call	_malloc			; HL = malloc(nelem * elsize)
	pop		de
	
	pop		bc				; BC = size

	add		hl,de
	or		a
	sbc		hl,de
	ret		z				; if (HL == NULL) return

	ld		e,0
	push	hl
	call	__ac_memset		; memset (HL, 0, size)
	pop		hl

	ret
