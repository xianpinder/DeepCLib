int strcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; ++s1, ++s2)
        if (*s1 == '\0')
			return 0;

    if (*s1 == 0)
        return -1;
    else if (*s2 == 0)
        return 1;
    else
        return *s1 - *s2;
}
