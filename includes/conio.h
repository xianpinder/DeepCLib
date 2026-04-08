#ifndef _CONIO_H
#define _CONIO_H
#include <sys/agon.h>

/* Note: with conio the top left co-ordinates are 1,1 */

struct text_info
{
	unsigned char winleft;				/* left window coordinate */
	unsigned char wintop;				/* top window coordinate */
	unsigned char winright;				/* right window coordinate */
	unsigned char winbottom;			/* bottom window coordinate */
	unsigned char attribute;			/* text attribute */
	unsigned char normattr;				/* normal attribute */
	unsigned char currmode;				/* screen mode */
	unsigned char screenheight;			/* text screen's height */
	unsigned char screenwidth;			/* text screen's width */
	unsigned char curx;					/* x-coordinate in current window */
	unsigned char cury;					/* y-coordinate in current window */
};

extern struct text_info _conio_info;

#define	BLACK 			 0
#define	RED 			 1
#define	BROWN 			 1
#define	GREEN 			 2
#define	YELLOW			 3
#define	BLUE 			 4
#define	MAGENTA 		 5
#define	CYAN 			 6
#define	LIGHTGRAY 		 7
#define	DARKGRAY 		 8
#define	LIGHTRED		 9
#define	LIGHTGREEN		10
#define	LIGHTYELLOW		11
#define	LIGHTBLUE 		12
#define	LIGHTMAGENTA	13
#define	LIGHTCYAN		14 
#define	WHITE			15

#define	BLINK		   	0

#define _NOCURSOR		0		/* Turns off the cursor */
#define _NORMALCURSOR	1		/* Normal underscore cursor */
#define _SOLIDCURSOR 	2		/* Solid block cursor */

#define	LASTMODE		255		/* Previous text mode */
#define	BW40			15		/* Black and white, 40 columns */
#define	C40				13		/* Color, 40 columns  */
#define	BW80			6		/* Black and white, 80 columns */
#define	C80				4		/* Color, 80 columns */
#define	MONO			6		/* Monochrome, 80 columns */
#define	C4350			0		/* EGA 43-line and VGA 50-line modes  */

#define clreol			_clreol
#define clrscr			_clrscr
#define cprintf 		_cprintf
#define cputs			_cputs
#define getch			_getch
#define getche			_getche
#define gettextinfo 	_gettextinfo
#define gotoxy			_gotoxy
#define kbhit			_kbhit
#define putch			_putch
#define textbackground	_textbackground
#define textcolor		_textcolor
#define textmode 		_textmode
#define wherex 			_wherex
#define wherey 			_wherey
#define window			_window

__asmcall void _ac_set_mode(int mode);
__asmcall void _ac_vdu_reqtxtpos(void);

void _clreol(void);
void _clrscr(void);
int _cprintf(const char *fmt, ...);
int _cputs(const char *str);	/* write a string directly to VDP */
int _getch(void);				/* read a character without echo, no Enter needed */
int _getche(void);				/* read a character with echo, no Enter needed */
void _gettextinfo(struct text_info *r);
void _gotoxy(int x, int y);
int _kbhit (void);
int _putch(int c);				/* write a character directly to VDP */
void _textbackground(int newcolor);
void _textcolor (int newcolor);
void _textmode(int newrnode);
void _window(int left, int top, int right, int bottom);
int _wherex(void);
int _wherey(void); 

//char *cgets(char *str); 
//int _cscanf(char *format, ...);
//void _delline (void);
//char *_getpass(const char *prompt);
//int _gettext(int left, int top, int right, int bottom, void *destin);
//void _highvideo(void);
//int _inp (unsigned portid);
//unsigned int _inpw(unsigned int portid);
//void _insline (void);
//void _lowvideo(void);
//int _movetext(int left, int top, int right, int bottom, int destleft, int desttop);
//void _norrnvideo(void);
//int _outp(unsigned int portid, int value);
//unsigned int outpw(unsigned int portid, unsigned int value);
//int _puttext(int left, int top, int right, int bottom, void *source); 
//void _setcursortype (int cur_t);
//void _textattr(int newattr);
//int _ungetch(int ch);

//extern int _directvideo;
//extern int _wscroll ;

#endif