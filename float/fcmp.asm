;
; Compares HL and DE as signed floats
;
; INPUTS:
;   HL - First 24-bit float
;   DE - Second 24-bit float
;
; OUTPUTS:
;   Z flag: Set if HL == DE
;   C flag: Set if HL < DE
;
; PRESERVES:
;   HL, DE, BC
;
					assume	ADL=1
					xdef	__fcmp

					section	code
__fcmp:
                    push    bc
                    push    hl
                    push    de

;-------------------------------------------------------------------------------
; Handle zero cases (mantissa = 0 means zero regardless of exponent/sign)
;-------------------------------------------------------------------------------

                    ld      a,h
                    or      l
                    jr      nz,@HLnotzero

                    ; HL is zero
                    ld      a,d
                    or      e
                    jr      z,@equal            ; Both zero
                    bit     0,e
                    jr      z,@HLless           ; DE positive: 0 < DE
                    jr      @HLgreater          ; DE negative: 0 > DE

@HLnotzero:
                    ld      a,d
                    or      e
                    jr      nz,@bothnotzero

                    ; HL non-zero, DE is zero
                    bit     0,l
                    jr      z,@HLgreater        ; HL positive: HL > 0
                    jr      @HLless             ; HL negative: HL < 0

;-------------------------------------------------------------------------------
; Both non-zero - compare signs
;-------------------------------------------------------------------------------

@bothnotzero:
                    ld      a,l
                    xor     e
                    and     $01
                    jr      z,@samesign

                    ; Signs differ: positive > negative
                    bit     0,l
                    jr      z,@HLgreater        ; HL positive, DE negative
                    jr      @HLless             ; HL negative, DE positive

;-------------------------------------------------------------------------------
; Same sign - compare magnitudes (exponent first, then mantissa)
;-------------------------------------------------------------------------------

@samesign:
                    ld      a,l
                    and     $01
                    ld      c,a                 ; C = sign (0=positive, 1=negative)

                    res     0,l                 ; Clear sign bits for magnitude comparison
                    res     0,e

                    ; Extract exponents using stack trick
                    dec     sp
                    push    hl
                    push    de
                    inc     sp
                    pop     af                  ; A = DEu
                    pop     hl                  ; H = HLu
                    ld      b,a                 ; B = DEu

                    ; Compare exponents: H = HLu, B = DEu (signed comparison)
                    ld      a,h                 ; A = HLu
                    sub     b                   ; A = HLu - DEu
                    jr      z,@sameexp

                    ; Handle signed overflow for correct comparison
                    jp      po,@expnoovf        ; No overflow, sign bit is valid
                    xor     $80                 ; Overflow: flip sign interpretation
@expnoovf:
                    ; Bit 7 of A indicates signed comparison result
                    jp      m,@HLmagsmaller

                    ; HL has larger magnitude
                    bit     0,c
                    jr      z,@HLgreater        ; Positive: larger mag = larger value
                    jr      @HLless             ; Negative: larger mag = smaller value

@HLmagsmaller:
                    ; HL has smaller magnitude
                    bit     0,c
                    jr      z,@HLless           ; Positive: smaller mag = smaller value
                    jr      @HLgreater          ; Negative: smaller mag = larger value

@sameexp:
                    ; Exponents equal - compare mantissas
                    ; C still contains the sign from @samesign

                    pop     de                  ; Restore original DE
                    pop     hl                  ; Restore original HL

                    ; Save originals again so exit points can restore them
                    push    hl
                    push    de

                    ; Clear sign bits for magnitude comparison
                    res     0,l
                    res     0,e

                    ; Unsigned 16-bit comparison
                    or      a                   ; Clear carry
                    sbc.s   hl,de               ; HL - DE
                    jr      z,@equal
                    jr      c,@HLmantless

                    ; HL mantissa > DE mantissa
                    bit     0,c
                    jr      z,@HLgreater        ; Positive: larger = greater
                    jr      @HLless             ; Negative: larger = less

@HLmantless:
                    ; HL mantissa < DE mantissa
                    bit     0,c
                    jr      z,@HLless           ; Positive: smaller = less
                    jr      @HLgreater          ; Negative: smaller = greater

;-------------------------------------------------------------------------------
; Exit points - restore registers and set flags
;-------------------------------------------------------------------------------

@equal:
                    pop     de
                    pop     hl
                    pop     bc
                    xor     a                   ; Z=1, C=0
                    ret

@HLgreater:
                    pop     de
                    pop     hl
                    pop     bc
                    or      $FF                 ; Z=0
                    or      a                   ; C=0
                    ret

@HLless:
                    pop     de
                    pop     hl
                    pop     bc
                    ld      a,1
					or		a                   ; Z=0
                    scf                         ; C=1
                    ret