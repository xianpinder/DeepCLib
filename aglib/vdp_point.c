#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_point (int x, int y)
{
	_vdun (2,25,69);
	_vduw (x);
	_vduw (y);
}
