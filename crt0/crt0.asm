; Deep C crt0.asm
                    ASSUME  ADL=1
					xref	_main
					xdef	_exit
					xdef	_errno
					xdef 	__getstkptr
					xdef	__bss_start
					xdef	__bss_length
					xdef	__heap_start
					xdef	__heap_end
					xdef	__sysvars
					xdef	__moskeymap
					xdef	__ac_memset

					xref	__low_bss
					xref	__len_bss
					xref	__parse_args
					xref	__argc
					xref	__argv
					xref	__init_fds
					xref	__close_fds
					xref	__atexits

                    jp      start
    
                    align   64
                    db      "MOS",0,1
start:
                    push    ix
                    push    iy
					ld		(stackptr),sp
					ld		sp,$0AFFFF

					push	hl				; push pointer to cmd line

					ld      a,8
					rst.lil 8
					ld      (__sysvars), ix

					ld		a,$1e
					rst.lil	8
					ld		(__moskeymap),ix

					call	initbss			; clear the bss data
					call	initheap		; setup the heap variables
					call	__parse_args	; arg 1 already on stack
					call	__init_fds		; initialise unix file descriptors

					ld		hl,__argv
					push	hl
					ld		hl,(__argc)
					push	hl
                    call    _main			; main (_argc, _argv)
finish:
					push	hl				; save return code
					call	__atexits		; process atexit() functions
					call	__close_fds		; close file handles
					pop		hl				; restore return code
					ld		sp,(stackptr)	; restore stack pointer
                    pop     iy
                    pop     ix
					add		hl,de
					or		a
					sbc		hl,de
					ret		z
					ld		de,30
					add		hl,de
                    ret

stackptr:			dl		0

_exit:
					pop		hl				; remove return addres
					pop		hl				; HL = exit code
					jr		finish

__getstkptr:      
					or		a
					sbc		hl,hl
					add		hl, sp
					ret

initbss:
					ld		hl,__low_bss
					ld		bc,__len_bss
					ld		e,0
__ac_memset:
					ld		a,e			; A = fill byte
					ex		de,hl		; DE = destination
					or		a
					sbc		hl,hl		; HL = 0
					sbc		hl,bc		; HL = 0 - BC
					ret		z			; length == 0 so return

					ld		(de),a
					dec		bc
					or		a
					sbc		hl,hl
					sbc		hl,bc
					ret		z			; length == 1 so return

; at least 1 more byte to clear so use LDIR
					push	de
					pop		hl			; HL = DE
					inc		de
					ldir
					ret

initheap:
					ld		hl,__low_bss
					ld		bc,__len_bss
					add		hl,bc
					ld		(__heap_start),hl
					ld		hl,$0AFFFF
					ld		(__heap_end),hl
					ret

__sysvars:			dl		0
__moskeymap:		dl		0
__bss_start:		dl		__low_bss
__bss_length:		dl		__len_bss
__heap_start:		dl		0
__heap_end:			dl		0
_errno:				dl		0
