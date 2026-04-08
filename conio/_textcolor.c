#include <sys/agon.h>
#include <conio.h>

void _textcolor (int newcolor)
{
	_ac_vdu(17);
	_ac_vdu(newcolor);
}
