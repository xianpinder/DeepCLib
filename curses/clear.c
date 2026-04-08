#include <agon/mos.h>
#include <curses.h>

int clear (void)
{
    vdp_clear_screen();
	return OK;
}
