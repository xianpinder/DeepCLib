					assume 	ADL=1
					xdef	__inkey
					xref	__moskeymap

					section	code
__inkey:
					pop		de
					ex		(sp),hl
					push	de
					
					ld		de,(__moskeymap)
					bit		7,l
					jr		nz,@negkey

					ld		b,16
					ld		c,0
@loop:
					ld		a,(de)
					or		a
					jr		nz,@found

					inc		de
					inc		c
					djnz	@loop

; if we get to here then nothing was pressed
					or		a							; clear the carry flag
					sbc		hl,hl						; HL = 0
					ret									; return 0

; we found a key down
@found:
					sla		c
					sla		c
					sla		c							; C = C * 8
@rotate:
					inc		c
					rra
					jr		nc,@rotate
					dec		c
					
					ld		a,c
					cpl
					ld		hl,$FFFFFF
					ld		l,a
					ret

@negkey:
					ld		a,l
					cpl									; convert -ve key code

					or		a
					sbc		hl,hl
					ld		l,a
					srl		l
					srl		l
					srl		l
					add		hl,de
					ex		de,hl

					or		a
					sbc		hl,hl
					and		7
					ld		l,a
					ld		bc,@bit_masks
					add		hl,bc

					ld		a,(de)
					and		(hl)
					ld		hl,1
					ret		nz
					dec		hl
					ret

@bit_masks:			db		1,2,4,8,16,32,64,128
