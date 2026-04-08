void *memset (void *s, int c, int n)
{
	const unsigned char uc = c;
	unsigned char *su = (unsigned char *)s;

	for (; 0 < n; ++su, --n)
		*su = uc;

	return s;
}