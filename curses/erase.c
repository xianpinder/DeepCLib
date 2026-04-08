#include <agon/mos.h>
#include <curses.h>

int erase (void)
{
    vdp_clear_screen();
	return OK;
}
