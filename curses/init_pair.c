#include <curses.h>

short global_color_pairs [COLOR_PAIRS*2];	//global to acurses only

int init_pair(short pair, short f, short b)
{
	if (pair < COLOR_PAIRS && pair >= 0)
	{
		global_color_pairs[pair*2] = f;
		global_color_pairs[(pair*2)+1] = b;
		return OK;
	}

	return ERR;
}