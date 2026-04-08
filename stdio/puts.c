
extern int putchar(int c);

int puts (const char *s)
{
	char *ptr = s;
	
	while (*ptr != (char)0)
	{
		putchar (*ptr++);
	}
	
	putchar ('\n');

	return 0;
}
