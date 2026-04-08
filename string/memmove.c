void *memmove(void *s1, const void *s2, int n)
{
	char *sc1 = (char *)s1;
	const char *sc2 = (const char *)s2;

	if (sc2 < sc1 && sc1 < sc2 + n)
		for (sc1 += n, sc2 += n; 0 < n; --n)
			*--sc1 = *--sc2;
	else
		for (; 0 < n; --n)
			*sc1++ = *sc2++;

	return s1;
}