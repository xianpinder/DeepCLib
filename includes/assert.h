#undef assert

#ifdef NDEBUG
#define assert(test)	((void)0)
#else
void __assert(char *);

#define _STR(x)	_VAL(x)
#define _VAL(x)	#x
#define assert(test) ((test) ? (void)0 : __assert(__FILE__ ":" _STR(__LINE__) " " #test))
#endif

#define static_assert _Static_assert
