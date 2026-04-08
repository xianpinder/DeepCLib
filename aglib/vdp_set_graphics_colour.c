#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_set_graphics_colour (int mode, int colour)
{
	_vdun (3, 18, mode, colour);
}
