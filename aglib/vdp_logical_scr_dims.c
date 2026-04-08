#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_logical_scr_dims (int is_on)
{
	_vdun (4, 23, 0, 0xC0, is_on);
}
