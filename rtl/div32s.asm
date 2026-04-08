	assume	ADL=1
	xdef	__div32s
	xref	__neg32
	xref	__negde32
	xref	__div32u
	
	section	code

__div32s:
    push    ix
    ld      b,0           	; Quotient / remainder sign counter

    bit     7,a
    jr      z,@hl_pos
    inc     b               ; Toggle quotient sign
	set 	7,b				; Remainder needs negation
    call    __neg32
@hl_pos:

    bit     7,c
    jr      z,@de_pos
    inc     b             ; Toggle quotient sign
    call    __negde32
@de_pos:

    call    __div32u

    bit     7,b            ; Remainder needs negation?
    jr      z,@rem_pos
    call    __negde32
@rem_pos:

	bit     0,b           	; Quotient sign
    pop     ix
    ret     z               ; Even: no negation needed
    jp      __neg32