#include <stdlib.h>
#include <sys/agon.h>

static char envbuf[128];

char *getenv(const char *name)
{
	int len;

	len = _ngetenv (name, envbuf, sizeof(envbuf));
	if (len == 0)
		return NULL;

	return envbuf;
}
