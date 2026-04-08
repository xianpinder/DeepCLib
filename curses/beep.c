#include <stdio.h>
#include <curses.h>

int beep(void)
{
	putchar(7);
	return OK;
}
