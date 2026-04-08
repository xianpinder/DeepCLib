    .assume ADL=1

    xdef __div32u

; AHL = AHL / CDE, CDE = AHL % CDE (unsigned)
__div32u:
	push	ix
	ld		ixh,b			; Save B to IXH

	push	hl
	pop		iy
	ld		b,a				; B,IY = AHL

	xor		a
    sbc		hl,hl			; HL = remainder
    
    ld      ixl,32          ; 32 bits
@loop:
	add		iy,iy
	rl		b				; Shift dividend left

	adc     hl,hl           ; Shift carry into remainder (low 24)
    adc     a,a             ; Shift remainder (high byte)
    jr      c,@overflow     ; 33-bit remainder, divisor definitely fits

    or      a,a             ; Clear carry
    sbc     hl,de           ; Try to subtract divisor
    sbc     a,c
    jr      nc,@fits
    add     hl,de           ; Doesn't fit, restore remainder
    adc     a,c
    jr      @next
@overflow:
    or      a,a             ; Clear carry
    sbc     hl,de           ; Subtract divisor (guaranteed to fit)
    sbc     a,c
@fits:
    inc     iy              ; Set bit in quotient
@next:
	dec		ixl
    jr    	nz,@loop
    
    ex      de,hl
	ld		c,a				; CDE = remainder
	lea		hl,(iy+0)
	ld		a,b				; AHL = quotient
 
	ld		b,ixh
	pop		ix
    ret
