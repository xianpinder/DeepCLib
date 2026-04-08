#include <sys/agon.h>
#include <agon/vdp.h>

void vdp_clear_screen (void)
{
	_ac_vdu(12);
}
