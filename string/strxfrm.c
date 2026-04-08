
extern int strncpy();
extern int strlen();

int strxfrm (char *s1, const char *s2, int n)
{
	if (n == 0)
		return strlen(s2);
	
	strncpy (s1, s2, n);
}
