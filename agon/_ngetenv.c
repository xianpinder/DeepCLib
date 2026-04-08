#include <stddef.h>
#include <string.h>
#include <sys/agon.h>

typedef int (*funcp)(const char *, void *, char **, int *, unsigned char *);

int _ngetenv (const char *name, char *buf, int len)
{
	int rc;
	unsigned char type = 3;
	char *actname = NULL;

	funcp readVarVal = (funcp) _mos_getfunction(10); 

	rc = readVarVal (name, buf, &actname, &len, &type);
	
	if ((rc != 0) || (len == 0) || (strcmp(name, actname) != 0))
	{
		buf[0] = '\0';
		return 0;
	}

	return len;
}
