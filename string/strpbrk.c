extern char *strchr();

char *strpbrk(char *string, char *set)
{
	while (*string)
	{
		if(strchr(set, *string))
			return string;
		++string;
	}

	return 0;
}
