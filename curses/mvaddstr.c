#include <agon/vdp.h>
#include <curses.h>

int mvaddstr (int y, int x, const char *str)
{
    vdp_cursor_tab (x, y);
    addstr(str);
    return OK;
}
