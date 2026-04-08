#include <curses.h>

void timeout(int delay)
{
	wtimeout(stdscr, delay);
}
