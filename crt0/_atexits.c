
/*
 * Defines and variables used by atexit().
 */

#define MAX_AT 32

int _Ats_Avail = MAX_AT;
void (*_At_List[MAX_AT])(void);

void _atexits(void)
{
	while (_Ats_Avail < MAX_AT)
        (*_At_List[_Ats_Avail++])();
}