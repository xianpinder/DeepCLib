				assume ADL = 1
			
				xdef	_clock
				xref	__sysvars

sysvar_time:	equ	 0

				section	code
_clock:
				ld		iy,(__sysvars)
				ld		hl, (iy+sysvar_time)
				ld 		a,  (iy+sysvar_time+3)
				ret