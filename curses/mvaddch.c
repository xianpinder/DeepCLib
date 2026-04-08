#include <agon/vdp.h>
#include <curses.h>

int mvaddch(int y, int x, const chtype ch)
{
    vdp_cursor_tab (x, y);
    return addch(ch);
}
