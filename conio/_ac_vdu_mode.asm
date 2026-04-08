			assume	ADL=1
			
			xdef	__ac_vdu_mode
			xref	__sysvars
			xref	__ac_vdu

__ac_vdu_mode:
			ld		iy,(__sysvars)
			res		4,(iy+4)
			push	hl
			ld		l,22
			call	__ac_vdu
			pop		hl
			call	__ac_vdu
@loop:
			bit		4,(iy+4)
			jr		z,@loop
			ret