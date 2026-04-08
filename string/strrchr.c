char *strrchr(char *s, int ch)
{
	char *sc = 0;

	for (;;)
	{
		if (*s == ch)
			sc = s;

		if (*s == '\0')
			return sc;
		
		++s;
	}
}