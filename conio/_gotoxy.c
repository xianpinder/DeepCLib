#include <sys/agon.h>
#include <conio.h>

void _gotoxy(int x, int y)
{
	_ac_vdu(31);
	_ac_vdu(x-1);
	_ac_vdu(y-1);
}
