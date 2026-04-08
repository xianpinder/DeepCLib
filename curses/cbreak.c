#include <curses.h>

//The cbreak routine disables line buffering and erase/kill character-processing
// (interrupt and flow control characters are unaffected), making characters typed by the user immediately available to the program. 
int cbreak()
{
	return ERR;
}