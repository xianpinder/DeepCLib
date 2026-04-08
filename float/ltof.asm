					assume	ADL=1

					xdef	__ltof
					xref	__ultof
					xref	__neg32
					
					section	code
__ltof:
					bit		7,a
					jp		z,__ultof				; +ve so use __ultof
					call	__neg32					; AHL = -AHL
					call	__ultof					; convert unsigned long AHL to float HL
					set		0,l						; float HL = -HL
					ret
