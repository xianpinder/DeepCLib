			assume ADL=1

			section code
			xdef	_vdp_get_scr_dims
			xref	__sysvars
			xref	__ac_vdp_write

_vdp_get_scr_dims:
			pop		de
			ex		(sp),hl
			push	de
			
			ld		iy,(__sysvars)

			add		hl,de
			or		a
			sbc		hl,de
			push	af
			jr		z,@nores
			res		4,(iy+4)
@nores:
			ld		hl,@req_mode
			ld		de,3
			call	__ac_vdp_write

			pop		af
			ret		z
@loop:
			bit		4,(iy+4)
			jr		z,@loop
			ret

@req_mode:	db		23,0,$86
