					assume	ADL=1

					xdef	__ftol
					xref	__ftoul
					xref	__neg32
					
					section	code
__ftol:
					bit		0,l
					jp		z,__ftoul
					res		0,l
					call	__ftoul
					jp		__neg32