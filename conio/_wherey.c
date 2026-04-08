#include <stddef.h>
#include <conio.h>

int _wherey(void)
{
	_gettextinfo(NULL);
	
	return _conio_info.cury;
}