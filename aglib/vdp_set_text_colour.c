#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_set_text_colour (int c)
{
	_ac_vdu (17);
	_ac_vdu (c);
}
