#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_cursor_enable (int flag)
{
	_vdun (3, 23, 1, flag);
}
