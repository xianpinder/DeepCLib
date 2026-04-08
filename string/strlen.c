int strlen(const char *s)
{
	const char *ep;

	for (ep = s; *ep != '\0'; ++ep)
		;

	return ep - s;
}