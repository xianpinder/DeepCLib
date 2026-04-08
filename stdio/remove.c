#include <unistd.h>

int remove(char *filename)
{
	return unlink (filename);
}
