#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_cursor_behaviour (int setting, int mask)
{
	_vdun (4, 23, 16, setting, mask);
}