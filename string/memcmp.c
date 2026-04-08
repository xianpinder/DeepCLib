int memcmp (const void *s1, const void *s2, int n)
{
	const unsigned char *us1 = (const unsigned char *)s1;
	const unsigned char *us2 = (const unsigned char *)s2;

	for (; 0 < n; ++us1, ++us2, --n)
	{
		if (*us1 != *us2)
			return *us1 < *us2 ? -1 : 1;
	}
	return 0;
}

