					assume	ADL=1

					xdef	__utof

					section	code

; convert a 24bit positive int in HL to a 24bit float in HL
; Preserves A, BC and DE
__utof:
					add		hl,de
					or		a
					sbc		hl,de
					ret		z						; int zero equals float zero

					push	af
					push	bc
					push	de

					ex		de,hl

					dec		sp
					push	de
					inc		sp
					pop		bc						; B = DEu

					ld		hl,$180000				; HLu = 24
					ld		h,b
					ld		l,d
					ld		a,e

					ld		de,$FF0000
@loop:
					bit		7,h
					jr		nz,@done				; float is now normalised

					add		a,a
					rl		l
					rl		h						; HLA = HLA << 1
					add		hl,de					; HLu = HLu - 1
					jr		@loop
@done:
					res		0,l						; ensure sign bit is positive
					pop		de
					pop		bc
					pop		af
					ret
