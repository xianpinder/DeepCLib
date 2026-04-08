			assume	ADL=1
			
			xdef	__ac_vdu_reqtxtpos
			xref	__sysvars
			xref	__ac_vdp_write

__ac_vdu_reqtxtpos:
			ld		iy,(__sysvars)
			res		0,(iy+4)
			ld		hl,@req_curs
			ld		de,3
			call	__ac_vdp_write
@loop:
			bit		0,(iy+4)
			jr		z,@loop
			ret

@req_curs:	db		23,0,$82