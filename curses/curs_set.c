#include <agon/mos.h>
#include <curses.h>

/*
 * The curs_set routine sets the cursor state is set to invisible, normal, or very visible
 * for visibility equal to 0, 1, or 2 respectively. If the terminal supports the visibility requested,
 * the previous cursor state is returned; otherwise, ERR is returned.
 *
 * this is a bit of a kludge but should work
 */

int curs_set(int visibility)
{
	switch (visibility)
	{
		case 0:
			vdp_cursor_enable(false);
			return 0;
		case 1:
			vdp_cursor_enable(true);
			return 1;
		case 2:
			vdp_cursor_enable(true);
			return 2;
	}

	return ERR;
}