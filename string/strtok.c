
char *strchr(char *, int);

static char *_strtok = 0;

char *strtok(char *string, char *delim)
{
	char *p;

	if (string == 0)
		string = _strtok;

	while (*string && strchr(delim, *string))
		++string;

	if (*string == '\0')
		return 0;

	p = string;
	while (*string && !strchr(delim, *string))
		++string;

	if(*string != '\0')
		*string++ = '\0';

	_strtok = string;

	return p;
}
