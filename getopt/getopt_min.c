#include <stdio.h>
#include <string.h>
#include <getopt.h>

#undef getopt

static int optpos = 1;

int getopt(int argc, char *const argv[], const char *optstring)
{
    const char *p;

    optarg = NULL;

    if (optind >= argc)
        return -1;

    /* Skip non-option arguments */
    if (argv[optind][0] != '-' || argv[optind][1] == '\0')
        return -1;

    /* Handle "--" end-of-options marker */
    if (argv[optind][1] == '-' && argv[optind][2] == '\0') {
        optind++;
        return -1;
    }

    optopt = argv[optind][optpos];

    p = strchr(optstring, optopt);
    if (p == NULL) {
        /* Unrecognised option */
        if (opterr)
            fprintf(stderr, "%s: illegal option -- %c\n", argv[0], optopt);
        if (argv[optind][++optpos] == '\0') {
            optind++;
            optpos = 1;
        }
        return '?';
    }

    if (p[1] == ':') {
        /* Option requires an argument */
        if (argv[optind][optpos + 1] != '\0') {
            /* Argument is remainder of current argv element: -dfoo */
            optarg = &argv[optind][optpos + 1];
        } else if (optind + 1 < argc) {
            /* Argument is next argv element: -d foo */
            optarg = argv[++optind];
        } else {
            if (opterr)
                fprintf(stderr, "%s: option requires an argument -- %c\n",
                        argv[0], optopt);
            optind++;
            optpos = 1;
            return optstring[0] == ':' ? ':' : '?';
        }
        optind++;
        optpos = 1;
    } else {
        /* No argument - advance position */
        if (argv[optind][++optpos] == '\0') {
            optind++;
            optpos = 1;
        }
    }

    return optopt;
}
