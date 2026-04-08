#include <sys/agon.h>
#include <conio.h>

void _window(int left, int top, int right, int bottom)
{
	_vdun(5, 28, (left)-1, (bottom)-1, (right)-1, (top)-1);

	_conio_info.winleft = left;
    _conio_info.wintop = top;
    _conio_info.winright = right;
    _conio_info.winbottom = bottom;
}
