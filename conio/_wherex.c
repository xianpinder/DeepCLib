#include <stddef.h>
#include <conio.h>

int _wherex(void)
{
	_gettextinfo(NULL);
	
	return _conio_info.curx;
}