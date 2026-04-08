#include <agon/vdp.h>
#include <curses.h>
#include <stdarg.h>

static char _curse_buf[512];

int printw(const char *fmt,...)
{
    va_list argp;
    int code;

    va_start(argp, fmt);
    vsprintf(_curse_buf, fmt, argp);
	code = addstr(_curse_buf);
    va_end(argp);

    return code;
}


int vw_printw(int win, const char *fmt,...)
{
	char *buf;
    va_list argp;
    int code;

    va_start(argp, fmt);
    vsprintf(_curse_buf, fmt, argp);
	code = addstr(_curse_buf);
    va_end(argp);

    return code;
}

int mvprintw(int y, int x, const char *fmt, ...)
{
    va_list argp;
    int code;

    vdp_cursor_tab( x, y);
    va_start(argp, fmt);
    vsprintf(_curse_buf, fmt, argp);
	code = addstr(_curse_buf);
    va_end(argp);

    return code;
}
