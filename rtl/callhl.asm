    .assume ADL=1

    xdef	__callhl

; __callhl: Call address in HL (for indirect function calls)

__callhl:
    jp      (hl)
