#include <stdio.h>
#include <stdlib.h>

void __assert (char *str)
{
	fputs ("Assertion failed: ", stderr);
	fputs (str, stderr);
	fputs ("\n", stderr);
	abort();
}
