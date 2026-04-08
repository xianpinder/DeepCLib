char *strchr(char *, int);

int strspn(char *string, char *set)
{
	int n = 0;

	while(*string && strchr(set, *string++))
		++n;

	return n;
}
