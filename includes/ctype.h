#ifndef _CTYPE_H
#define _CTYPE_H

int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);

#define _AN (1)
#define _AL (2)
#define _CT (4)
#define _DG (8)
#define _GR (16)
#define _LO (32)
#define _PR (64)
#define _PN (128)
#define _SP (256)
#define _UP (512)
#define _HX (1024)

#define isalnum(c)	(_CyTab[(int)(c)] & _AN)
#define isalpha(c)	(_CyTab[(int)(c)] & _AL)
#define iscntrl(c)	(_CyTab[(int)(c)] & _CT)
#define isdigit(c)	(_CyTab[(int)(c)] & _DG)
#define isgraph(c)	(_CyTab[(int)(c)] & _GR)
#define islower(c)	(_CyTab[(int)(c)] & _LO)
#define isprint(c)	(_CyTab[(int)(c)] & _PR)
#define ispunct(c)	(_CyTab[(int)(c)] & _PN)
#define isspace(c)	(_CyTab[(int)(c)] & _SP)
#define isupper(c)	(_CyTab[(int)(c)] & _UP)
#define isxdigit(c)	(_CyTab[(int)(c)] & _HX)

extern unsigned int *_CyTab;

#endif
