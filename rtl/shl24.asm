    .assume ADL=1

    xdef __shl24

; HL = HL << DE (shift count in E)

__shl24:
	inc		e
@loop:
	dec		e
	ret		z
    add     hl,hl           ; Shift left by 1
	jr		@loop
