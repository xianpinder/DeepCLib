    .assume ADL=1

    xdef __shl32

; AHL = AHL << CDE (shift count in E)

__shl32:
	inc		e
@loop:
	dec		e
	ret		z
    add     hl,hl           ; Shift left by 1
	adc		a,a
	jr		@loop
