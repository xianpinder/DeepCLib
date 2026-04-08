#include <sys/agon.h>
#include <agon/vdp.h>

static unsigned char vdu_data[3] = {23, 0, 0x91};

void vdp_reset_system_font (void)
{
	_vdp_write(vdu_data, sizeof(vdu_data));
}
