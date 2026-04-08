;
; __asmcall void _ac_vdu (int ch);
;
		.assume	ADL=1

		xdef	__ac_vdu

		section	code

__ac_vdu:
        ld      a,l
		rst.lil	$10
        ret
