	.assume ADL=1
	
	xdef _setjmp
	xdef _longjmp

;------------------------------------------------------------
; setjmp - Save execution context
; Input: Argument on stack = pointer to jmp_buf
; Output: HL = 0
;------------------------------------------------------------
_setjmp:
    ld      iy,0
    add     iy,sp
    ld      hl,(iy+3)       ; HL = pointer to jmp_buf
    
    ; Save SP (value it will have after we return)
	lea		de,iy+3			; DE = SP after return
    ld      (hl),de
    inc     hl
    inc     hl
    inc     hl
    
    ; Save IX
    ld      (hl),ix
    inc     hl
    inc     hl
    inc     hl
    
    ; Save return address
    ld      de,(iy+0)
    ld      (hl),de
    
    ; Return 0
    or		a
	sbc		hl,hl
    ret

;------------------------------------------------------------
; longjmp - Restore execution context and jump
; Input: First arg = pointer to jmp_buf
;        Second arg = return value (will be returned by setjmp)
;------------------------------------------------------------
_longjmp:
    ld      iy,0
    add     iy,sp
    ld      hl,(iy+3)       ; HL = pointer to jmp_buf
    ld      bc,(iy+6)       ; BC = return value
    
    ; If val == 0, set to 1
    ld      a,(iy+8)		; A = BC upper byte
	or		b
    or      c
    jr      nz,@skip
    inc		bc
@skip:
    
    ; Load saved values
    ld      iy,(hl)         ; IY = saved SP
    inc     hl
    inc     hl
    inc     hl
    
    ld      ix,(hl)         ; restore IX
    inc     hl
    inc     hl
    inc     hl
    
    ld      hl,(hl)         ; HL = return address
    
    ; Set up new stack
    ld      sp,iy           ; Restore SP
    push    hl              ; Push return address
    
    ; Return value in HL
	push	bc
	pop		hl
    
    ret                     ; Jump to saved return address