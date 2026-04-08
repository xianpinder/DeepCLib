#include <curses.h>

int pair_content (short pair, short *f, short *b)
{
	if (pair < COLOR_PAIRS && pair >= 0)
	{
		*f = global_color_pairs[pair*2];
		*b = global_color_pairs[(pair*2)+1];
		return OK;
	}

	return ERR;
}
