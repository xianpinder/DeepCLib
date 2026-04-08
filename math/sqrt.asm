;
; floating point square root
;
					.assume	ADL=1

					xdef	_sqrt
					xdef	_sqrtf
					xref	__fadd
					xref	__fdiv

FLT_INF:			EQU		$7FFFFE

					section	code
_sqrtf:
_sqrt:
					pop		de
					ex		(sp),hl
					push	de

; first check if HL = 0 and just return if it is
					ld		a,h
					or		l
					ret		z

; can't find square root of negative numbers so check
; if HL is negative and return error if it is					
					bit		0,l
					jr		z,@isokay
					ld		hl,FLT_INF
					ret

; have valid number in HL
@isokay:
					push	hl

; approixmate floating point square root using lookup table
; sqrt(mantissa * 2^exp) = sqrt(mantissa) * 2^(exp/2)


; move the exponent from the high byte of HL into B
					dec		sp
					push	hl
					inc		sp
					pop		bc					; B = exponent

; we need to halve the exponent so first check to see if it is odd
					bit		0,b
					jr		z,@even

; exponent is odd so need to increment it and
; shift the mantissa right one place.

					inc		b
					srl		h
					rr		l
@even:
; shift HL right 7 places so we have the top 9 bits of the mantissa
					xor		a
					sla		l
					rl		h
					rla							; AHL = HL << 1
					ld		l,h
					ld		h,a					; HL = AHL >> 8

; HL is now between 128 and 511
; subtract 128 so HL is between 0 and 383

					ld		de,128				; DE = 128
					or		a
					sbc		hl,de				; HL = HL - 128
					ld		d,h
					ld		e,l
;
; index into the sqrt table
;
					ld		hl,float_sqrt_table
					add		hl,de
					ld		a,(hl)
					
; the exponent will be halved so we only use the top 7 bits of it
; we need bit zero of uHL (which will become top bit) to be
; the same as the current top bit of H (like we did a signed shift right)

					ld		h,b					; put the exponent into H
					add		hl,hl				; move bit 7 of H into bit 0 of uHL
					ld		h,b					; put the exponent back in to H

					set		0,h
					ld		l,a					; put A+256 into HL

; shift HL left 7 places
; this puts the mantissa into place and halves the exponent at the same time

					add		hl,hl
					add		hl,hl
					add		hl,hl
					add		hl,hl
					add		hl,hl
					add		hl,hl
					add		hl,hl				; HL = HL << 7

					pop		de
					push	hl
					ex		de,hl				; DE = number, HL = approx sqrt(number)
					call	__fdiv
					pop		de
					call	__fadd

					ld		de,$FF0000
					add		hl,de				; HL = (a + x/a)/2
					ret

					section	data
float_sqrt_table:
					db		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,16,17,18,19,20,21,22,23,24
					db		25,26,27,28,28,29,30,31,32,33,34,35,36,36,37,38,39,40,41,42,42,43,44
					db		45,46,47,48,48,49,50,51,52,53,53,54,55,56,57,58,58,59,60,61,62,62,63
					db		64,65,66,66,67,68,69,70,70,71,72,73,73,74,75,76,77,77,78,79,80,80,81
					db		82,83,83,84,85,86,86,87,88,89,89,90,91,92,92,93,94,95,95,96,97,97,98
					db		99,100,100,101,102,102,103,104,105,105,106,107,107,108,109,110,110
					db		111,112,112,113,114,114,115,116,116,117,118,119,119,120,121,121,122
					db		123,123,124,125,125,126,127,127,128,129,129,130,131,131,132,133,133
					db		134,135,135,136,137,137,138,139,139,140,140,141,142,142,143,144,144
					db		145,146,146,147,148,148,149,149,150,151,151,152,153,153,154,154,155
					db		156,156,157,158,158,159,159,160,161,161,162,162,163,164,164,165,166
					db		166,167,167,168,169,169,170,170,171,172,172,173,173,174,175,175,176
					db		176,177,177,178,179,179,180,180,181,182,182,183,183,184,185,185,186
					db		186,187,187,188,189,189,190,190,191,191,192,193,193,194,194,195,195
					db		196,197,197,198,198,199,199,200,200,201,202,202,203,203,204,204,205
					db		206,206,207,207,208,208,209,209,210,210,211,212,212,213,213,214,214
					db		215,215,216,216,217,218,218,219,219,220,220,221,221,222,222,223,223
					db		224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,232
					db		233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241
					db		242,242,243,243,244,244,245,245,246,246,247,247,248,248,249,249,250
					db		250,251,251,252,252,253,253,254,254,255,255
