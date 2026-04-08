#include <ctype.h>
#include <stddef.h>

int _strncasecmp(const char *s1, const char *s2, size_t n)
{
    while (n-- && *s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        ++s1;
        ++s2;
    }
    if (n == (size_t)-1) return 0;
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
