#include <agon/vdp.h>
#include <curses.h>

int wmove(int win, int y, int x)
{
    vdp_cursor_tab (x, y);

    return OK;
}

int move (int y, int x)
{
    vdp_cursor_tab (x, y);

    return OK;
}
