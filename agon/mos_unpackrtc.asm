;
; void _mos_unpackrtc (void *rtcbuffer, int flags);
;
		.assume	ADL=1

		xdef	__mos_unpackrtc

		section	code
__mos_unpackrtc:
		push	ix
		ld		ix,0
		add		ix,sp

		ld		hl,(ix+6)
		ld		c,(ix+9)
        ld      a,$23
		rst.lil	$8

		pop		ix
        ret
