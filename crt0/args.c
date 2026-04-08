#include <string.h>

#define MAX_ARGS	(32)
#define BUF_SIZE	(255)

int _argc;
char *_argv[MAX_ARGS+1];
static char argbuf[BUF_SIZE+1];

void _parse_args (char *cmdline)
{
    char delim;
	int cmdlen;
	int namelen;
    char *p;
    char *start;

	strcpy (argbuf, "prog.bin ");

	namelen = strlen(argbuf);
	cmdlen = strlen(cmdline);
	if (cmdlen != 0)
	{
		if ((namelen + cmdlen) >= BUF_SIZE)
			cmdlen = BUF_SIZE - namelen - 1;
		strncat (argbuf, cmdline, cmdlen);
		argbuf[BUF_SIZE] = '\0';
	}

    /*
     * Trim any trailing non-white space (like a newline).
     */

    p = &argbuf[strlen(argbuf) - 1];
    while (p > argbuf && *p < ' ')
		*p-- = '\0';

	/*
	 * Split the command line buffer into individual arguments,
	 * handling single and double quoted strings. 
	 * Modifies argbuf in place (inserts null terminators).
	 *
	 * The quotes themselves are stripped from the arguments.
	 * An unterminated quote runs to end of string.
	 *
	 * After processing, _argc and _argv are ready to
	 * pass to main(_argc, _argv).
	 */

    _argc = 0;
    p = argbuf;

    while (*p)
	{
        /* Skip leading whitespace */
        while (*p == ' ' || *p == '\t')
            ++p;

        if (*p == '\0')
            break;

        /* Determine start of argument and scan to end */
        if (*p == '\"' || *p == '\'')
		{
            delim = *p;
            ++p;                /* skip past the opening quote */
            start = p;          /* argument starts after quote */
            while (*p && *p != delim)
                ++p;
        }
		else
		{
            start = p;
            while (*p && *p != ' ' && *p != '\t')
                ++p;
        }

        /* Null-terminate this argument */
        if (*p)
            *p++ = '\0';

        /* Store in argv if there is room */
        if (_argc < MAX_ARGS)
            _argv[_argc++] = start;
    }

    _argv[_argc] = (char *)0;
}
