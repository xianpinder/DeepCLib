#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#undef raise

_SigFunc *_SignalTab[_NSIG] =
{
    SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,			/*  0-3  */
    SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,			/*  4-7  */
    SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,			/*  8-12 */
    SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL			/* 13-15 */
};

static char sigmess[] = "** Signal 00 occurred.\n";

int raise (int sig)
{
    _SigFunc *func;
    int len;
    char *str;

    if ((sig < 1) || (sig >= _NSIG))
        return -1;

    func = _SignalTab[sig];

    if (func == SIG_IGN)
        return 0;
    
    if (func == SIG_DFL)
    {
        switch (sig)
		{
			case SIGINT:
				str = "**BREAK\n";
				len = 8;
				break;
		
			case SIGABRT:
				str = "**ABORTED.\n";
				len = 11;
				break;

			default:
				sigmess[10] = (sig / 10) + '0';
				sigmess[11] = (sig % 10) + '0';
				str = sigmess;
				len = 23;
				break;
		}

		write (STDERR_FILENO, str, len);
		exit (EXIT_FAILURE);
    }

    _SignalTab[sig] = SIG_DFL;
    (*func)(sig);
    return 0;
}
