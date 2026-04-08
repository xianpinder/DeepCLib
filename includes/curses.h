// Agon curses library
// Copyright Shawn Sijnstra (c) 2024
// GPLv3 License
// Please let me know if you use the library, and anything you can add is welcome

// See if we can build a small curses library
// This version is using VDP calls so does not use any terminal characteristics
// A terminal mode version might be nice at a later date

// Note that there is a 512 byte buffer here for expanding out all of the printw style commands.

#ifndef _NCURSES_H
#define _NCURSES_H

#include <stdbool.h>

#ifndef FALSE
#define FALSE false
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifndef ERR
#define ERR (-1)
#endif

#ifndef OK
#define OK 0
#endif

#define getch _getch
#define kbhit _kbhit

#define CURSES 1
#define CURSES_H 1

/* These are defined only in curses.h, and are used for conditional compiles */
#define NCURSES_VERSION_MAJOR 0
#define NCURSES_VERSION_MINOR 1
#define NCURSES_VERSION_PATCH 0

/* This is defined in more than one ncurses header, for identification */
#undef  NCURSES_VERSION
#define NCURSES_VERSION "0.2"

typedef unsigned chtype;
typedef	chtype	attr_t;		/* ...must be at least as wide as chtype */

/* colors */
#define COLOR_BLACK		0
#define COLOR_RED		1
#define COLOR_GREEN		2
#define COLOR_YELLOW	3
#define COLOR_BLUE		4
#define COLOR_MAGENTA	5
#define COLOR_CYAN		6
#define COLOR_WHITE		7
#define COLOR_BG 		128

#define COLORS	16
#define COLOR_PAIRS 31

extern short global_color_pairs [COLOR_PAIRS*2];	//global to acurses only

#define COLOR_PAIR(n) 	((n) << 8)
#define PAIR_NUMBER(n)	((n) >> 8)

#define stdscr 0	//there is only 1 screen

/* CP437
#define ACS_BTEE	0xCA	//'+'	//bottom tee
#define ACS_BULLET	0xFE	//'~' // bullet //
#define ACS_HLINE	0xCD	//'-'	//horizontal line
#define ACS_LANTERN	'#'	//lantern symbol
#define ACS_LLCORNER	0xC8	//'+'	//lower left-hand corner
#define ACS_LRCORNER	0xBC	//'+'	//lower right-hand corner
#define ACS_LTEE	0xCC	//'+'	//left tee
#define ACS_RTEE	0xB9	//'+'	//right tee
#define ACS_TTEE	0xCB	//'+'	//top tee
#define ACS_ULCORNER	0xC9	//'+'	//upper left-hand corner
#define ACS_URCORNER	0xBB	//'+'	//upper right-hand corner
#define ACS_VLINE	0xBA	//'|'	//vertical line
*/

/* CP1252 */
//note: I'm replacing the obelisk with an expanded plus
#define ACS_BTEE	0x86 //'+'	//bottom tee
#define ACS_BULLET	0x95	//'~' // bullet //
#define ACS_HLINE	0x97	//'-'	//horizontal line
#define ACS_LANTERN	'#'	//lantern symbol
#define ACS_LLCORNER	0x86 //'+'	//lower left-hand corner
#define ACS_LRCORNER	0x86 //'+'	//lower right-hand corner
#define ACS_LTEE	0x86 //'+'	//left tee
#define ACS_RTEE	0x86 //'+'	//right tee
#define ACS_TTEE	0x86 //'+'	//top tee
#define ACS_ULCORNER	0x86 //'+'	//upper left-hand corner
#define ACS_URCORNER	0x86 //'+'	//upper right-hand corner
#define ACS_VLINE	'|'	//vertical line

#define KEY_UP	11
#define KEY_RIGHT 21
#define KEY_DOWN 10
#define KEY_LEFT 8
#define KEY_ENTER	13
/*
A_STANDOUT	0	1
A_UNDERLINE	1	2
A_REVERSE	2	4
A_BLINK   	3	8
A_DIM      	4	16
A_BOLD    	5	32
A_INVIS   	6	64
A_PROTECT	7	128
A_ALTCHARSET	8	256
*/
/*
#define A_NORMAL	0
#define A_STANDOUT	1
#define A_UNDERLINE	2
#define A_REVERSE	4
#define A_BLINK		8
#define A_DIM		16
#define A_BOLD		32
*/
#define A_NORMAL	0
#define A_STANDOUT	0
#define A_UNDERLINE	0
#define A_REVERSE	0
#define A_BLINK		0
#define A_DIM		0
#define A_BOLD		(32 << 8)

#define getyx(win,y,x)   	(y = getcury(win), x = getcurx(win))
#define getmaxyx(win,y,x)	(y = getmaxy(win), x = getmaxx(win))
#define box(win, v, h)		wborder(win, v, v, h, h, 0, 0, 0, 0)

int addstr(const char *str);
int start_color(void);
int erase(void);
int clear(void);
int clearok(int win, bool state);
int initscr();
int getcury(int win);
int getcurx(int win);
int getmaxy(int win);
int getmaxx(int win);
int init_color(short color, short r, short g, short b);
bool has_colors(void);
bool can_change_color(void);
int color_content(short color, short *r, short *g, short *b);
int curs_set(int visibility);
int printw(const char *fmt,...);
int vw_printw(int win, const char *fmt,...);
int mvprintw(int y, int x, const char *fmt, ...);
int init_pair(short pair, short f, short b);
int pair_content(short pair, short *f, short *b);
int use_default_colors(void);
int refresh(void);
int endwin(void);
bool isendwin (void);
int attron(const chtype attrs);
int attroff(int attrs);
int attr_get (attr_t *attr, int *n, int *m);
int wmove(int win, int y, int x);
int move(int y, int x);
int clrtoeol (void);
int addch(const chtype ch);
int mvaddch(int y, int x, const chtype ch);
int noecho (void);
int nonl (void);
int halfdelay(int tenths);
int addstr(const char *str);
int mvaddstr(int y, int x, const char *str);
int beep(void);
int keypad(int win, bool bf);
int nodelay(int win, bool bf);
void wtimeout(int win, int delay);
void timeout(int delay);
char wgetch(int win);
int savetty();
int resetty();
int cbreak();
int nocbreak();
int wborder(int win, chtype ls, chtype rs,	chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);
int	napms(int ms);

#endif
