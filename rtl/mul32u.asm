    .assume ADL=1

    xdef __mul32u

; AHL = AHL * CDE (unsigned)
; Uses shift-and-add algorithm
__mul32u:
    push    bc
    push    de
	push	ix
    
	push	hl
	pop		iy
	ld		b,a				; B,IY = AHL
    
    xor     a
    sbc     hl,hl           ; AHL = result accumulator
    
    ld      ixl,32
@loop:
    add     hl,hl           ; Shift result left (low 24 first)
    adc     a,a             ; Shift result left (high byte with carry)

	add		iy,iy
	rl		b				; Shift multiplicand left

    jr      nc,@skip
    add     hl,de           ; Add multiplier to result (low 24)
    adc     a,c             ; Add multiplier to result (high byte)
@skip:
	dec		ixl
    jr		nz,@loop
    
	pop		ix
    pop     de
    pop     bc
    ret
