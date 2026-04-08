int strncmp (char *s1, char *s2, int n)
{
    if (n == 0)
		return 0;

    for ( ; *s1 == *s2; ++s1, ++s2)
    {
        if (*s1 == '\0')
			return 0;
        if (--n == 0)
			break;
    }

    if (*s1 == '\0')
		return -1;
    if (*s2 == '\0')
		return 1;

    return *s1 - *s2;
}
