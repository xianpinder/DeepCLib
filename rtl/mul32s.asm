    .assume ADL=1

    xdef	__mul32s
	xref	__mul32u
	xref	__neg32
	xref 	__negde32

; AHL = AHL * CDE (signed)
; Handle signs, then use unsigned multiply
__mul32s:
	push	bc
	push	de
    ld		b,0  	  		; Sign flag
    
	bit		7,a				; check if AHL is negative
    jr      z,@hl_pos
    inc     b               ; toggle sign
	call	__neg32			; AHL = -AHL
@hl_pos:
    
  	bit		7,c				; Check if CDE is negative
    jr      z,@de_pos
    inc     b				; toggle sign
	call	__negde32		; CDE = -CDE
@de_pos:
    
    ; Do unsigned multiply
    call    __mul32u
    
    ; Apply sign if needed
    rr		b
	pop		de
	pop		bc
	ret		nc
	jp		__neg32
