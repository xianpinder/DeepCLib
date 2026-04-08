char *strcat (char *dest, const char *source)
{
    char *p = dest;

    while (*dest)
		++dest;

    while ((*dest++ = *source++) != (char)0)
		;

    return p;
}
