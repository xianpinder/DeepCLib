#include <sys/agon.h>
#include <agon/vdp.h>

static unsigned char vdu_data[] = {23, 27, 0, 0};

void vdp_select_bitmap (int n)
{
	vdu_data[3] = n;
	_vdp_write(vdu_data, sizeof(vdu_data));
}
