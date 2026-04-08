#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_define_colour(int l, int p, int r, int g, int b)
{
	_vdun (6, 19, l, p, r, g, b);
}
