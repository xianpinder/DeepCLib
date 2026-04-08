char *strncat(char *s1, char *s2, int n)
{
	char *p = s1;
	
	if (n == 0)
		return s1;
	
	while (*s1 != 0)
		s1++;
	
	while (*s2 != 0)
	{
		*s1++ = *s2++;
		if (--n == 0)
			break;
	
	}
	
	*s1 = 0;
	return p;
}
