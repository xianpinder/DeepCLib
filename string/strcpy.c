char *strcpy (char *s1, const char *s2)
{	
	char *ptr = s1;

	while ((*ptr++ = *s2++) != (char)0)
		;

	return s1;
}
