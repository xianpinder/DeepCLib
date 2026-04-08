#include <stdio.h>
#include <string.h>
#include <errno.h>

void perror(char *str)
{
    if (str != NULL)
    {
        if (*str != '\0')
            fprintf (stderr, "%s:", str);
    }

    fprintf (stderr, "%s\n", strerror(errno));
}
