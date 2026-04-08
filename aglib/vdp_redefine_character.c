#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_redefine_character (int ch, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8)
{
	_vdun (12, 23, 0, 0x90, ch, b1, b2, b3, b4, b5, b6, b7, b8);
}
