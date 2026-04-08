#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef int sig_atomic_t;
typedef void _SigFunc(int);

#define SIGINT	2
#define SIGILL	4
#define SIGABRT	6
#define SIGFPE	8
#define SIGSEGV	11
#define SIGTERM	15

#define _NSIG	16

#define SIG_DFL	(_SigFunc *)0
#define SIG_IGN	(_SigFunc *)1
#define SIG_ERR	(_SigFunc *)2

int raise(int);
_SigFunc *signal(int, _SigFunc *);

#endif
