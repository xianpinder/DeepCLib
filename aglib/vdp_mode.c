#include <sys/agon.h>
#include <agon/vdp.h>

int vdp_mode (int mode)
{
	_ac_vdu_mode (mode);
	return mode;
}
