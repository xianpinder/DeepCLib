#include <agon/vdp.h>
#include <curses.h>

#define RENDER_WITH_DEFAULT(ch,def) ch = ((ch == 0) ? def : ch)

int wborder(int win,
	chtype ls, chtype rs,
	chtype ts, chtype bs,
	chtype tl, chtype tr,
	chtype bl, chtype br)
{
	int	y,x,curx,cury,i;

	RENDER_WITH_DEFAULT(ls, ACS_VLINE);
    RENDER_WITH_DEFAULT(rs, ACS_VLINE);
    RENDER_WITH_DEFAULT(ts, ACS_HLINE);
    RENDER_WITH_DEFAULT(bs, ACS_HLINE);
    RENDER_WITH_DEFAULT(tl, ACS_ULCORNER);
    RENDER_WITH_DEFAULT(tr, ACS_URCORNER);
    RENDER_WITH_DEFAULT(bl, ACS_LLCORNER);
    RENDER_WITH_DEFAULT(br, ACS_LRCORNER);

    getmaxyx(win,y,x); y--; x--;
    getyx(stdscr, cury, curx);
    // void vdp_cursor_behaviour( int setting, int mask );
    vdp_cursor_behaviour (0x10, 0xFFEF); // turn off scroll
    mvaddch(0,0,tl);
    mvaddch(y,0,bl);
    mvaddch(0,x,tr);
    mvaddch(y,x,br);
	
    for (i=1;i<y;i++)
	{
    	mvaddch(i,0,ls);
    	mvaddch(i,x,rs);
    }

    for (i=1;i<x;i++)
	{
    	mvaddch(0,i,ts);
    	mvaddch(y,i,bs);
    }

    move(cury, curx);
    vdp_cursor_behaviour (0x10, 0xFFEF); // turn off scroll
	return OK;
}