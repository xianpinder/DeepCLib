#include <time.h>
#include <curses.h>

int	napms(int ms)
{
	clock_t timer = clock();

	ms = ms / 4;
	while (clock() < timer + ms) ;

	return OK;
}
