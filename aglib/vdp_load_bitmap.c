#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_load_bitmap (int w, int h, void *bitmap)
{
	_vdun (3, 23, 27, 1);
	_vduw (w);
	_vduw (h);
	_vdp_write (bitmap, w * h * 4);
}
