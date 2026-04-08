					assume	ADL=1

					xdef	__ultof
					xref	__utof
					
					section	code
__ultof:
					or		a
					jp		z,__utof				; if A = 0 then have 24bit number

					push	bc
					push	de

					ex		de,hl					; DE = HL

					dec		sp
					push	de
					inc		sp
					pop		bc						; B = DEu

					ld		hl,$200000				; HLu = 32
					ld		h,b
					ld		l,d

					ld		de,$010000
@loop:
					srl		a
					rr		h
					rr		l						; AHL = AHL >> 1
					add		hl,de					; HLu = HLu + 1
					or		a
					jr		nz,@loop

					res		0,l
					pop		de
					pop		bc
					ret