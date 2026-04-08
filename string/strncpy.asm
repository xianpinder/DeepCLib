			assume	ADL=1
			xdef	_strncpy
			xdef	__ac_strncpy

			section	code

_strncpy:
			ld		iy,0
			add		iy,sp
			ld		hl,(iy+3)		; HL = dst
			ld		de,(iy+6)		; DE = src
			ld		bc,(iy+9)		; BC = n

__ac_strncpy:
			push	hl
			or		a
			sbc		hl,hl
			sbc		hl,bc
			pop		hl
			ret		z				; if (n == 0) return

			push	hl				; save dst
			ex		de,hl			; HL = src, DE = dst
@cploop:
			ld		a,(hl)
			ldi
			jp		po,@done		; if BC == 0 then return
			or		a
			jr		nz,@cploop		; keep looping until copy zero across

			push	de
			pop		hl
			dec		hl				; HL = DE - 1 (position of terminating 0)
			ldir					; copy 0, BC times
@done:
			pop		hl
			ret
