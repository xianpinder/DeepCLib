
int strlen(char *);
int strncmp(char *, char *, int);
char *strchr(char *, int);

char *strstr (char *string, char *pattern)
{
    int plen;

    plen = strlen (pattern);
    if (plen == 0)
        return string;

    while ((string = strchr (string, *pattern)) != 0)
    {
		if (strncmp (string, pattern, plen) == 0)
			break;
		++string;
    }

    return string;
}
