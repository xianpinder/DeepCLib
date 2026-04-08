#include <agon/mos.h>
#include <curses.h>

int clearok(int win, bool bf)
{
    vdp_clear_screen();
    return OK;
}