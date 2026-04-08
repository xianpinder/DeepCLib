char *strncpy (char *s1, char *s2, int n)
{
    char *p = s1;

    while (n > 0)
    {
        n--;
        if ((*s1++ = *s2++) == 0)
			break;
    }

    while (n > 0)
    {
        *s1++ = '\0';
        n--;
    }
    
    return p;
}
