#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_cursor_tab (int x, int y)
{
	_vdun (3, 31, x, y);
}
