;
; asm version of strlen() using __asmcall
;
		assume	ADL=1

		xdef	_strlen
		xdef	__ac_strlen

		section	code
_strlen:
		pop		de
		ex		(sp),hl
		push	de

__ac_strlen:
		xor		a
		ld		bc, 0
		cpir
		sbc		hl, hl
		scf
		sbc		hl, bc
		ret
