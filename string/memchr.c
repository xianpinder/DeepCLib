void *memchr(const void *s, int c, int n)
{
	const unsigned char uc = c;
	const unsigned char *su = (const unsigned char *)s;

	for (; 0 < n; ++su, --n)
	{
		if (*su == uc)
			return (void *)su;
	}
	return 0;
}