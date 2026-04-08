#include <signal.h>

#undef signal

extern _SigFunc *_SignalTab[];

_SigFunc *signal(int signum, _SigFunc *func)
{
    _SigFunc *oldsig;

    if ((signum < 1) || (signum >= _NSIG) || (func == SIG_ERR))
        return SIG_ERR;

    oldsig = _SignalTab[signum];
    _SignalTab[signum] = func;
    return oldsig;
}
