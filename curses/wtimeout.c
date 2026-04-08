#include <curses.h>

//partial implementation - positive delay not done yet.
void wtimeout(int win, int delay)
{
	if (delay < 0)
		nodelay(win,false);
	else
		nodelay(win,true);
}
