char *strchr(char *s, int c)
{
	char ch = c;

	for (; *s != ch; ++s)
		if (*s == '\0')
			return 0;

	return s;
}