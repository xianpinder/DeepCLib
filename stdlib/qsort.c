/*
 * qsort.c - Quicksort (C89)
 *
 * void qsort(void *base, size_t nmemb, size_t size,
 *            int (*compar)(const void *, const void *));
 *
 * Median-of-three pivot selection with insertion sort
 * for small partitions. Byte-by-byte swap for portability
 * on unaligned or odd-sized elements (e.g. 3-byte pointers
 * on eZ80). Tail-call optimization limits stack depth to
 * O(log n).
 */

#include <stddef.h>

#define CUTOFF 10   /* switch to insertion sort below this */

/* Swap two elements of 'size' bytes */
static void swap(char *a, char *b, size_t size)
{
    char tmp;

    while (size--)
    {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

/* Insertion sort for small partitions */
static void isort(char *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *))
{
    char *i, *j;
    char *end = base + nmemb * size;

    for (i = base + size; i < end; i += size)
    {
        for (j = i; j > base; j -= size)
        {
            if (compar(j - size, j) <= 0)
                break;
            swap(j - size, j, size);
        }
    }
}

/* Sort three elements and return pointer to median */
static void sort3(char *a, char *b, char *c, size_t size,
                  int (*compar)(const void *, const void *))
{
    if (compar(a, b) > 0) swap(a, b, size);
    if (compar(b, c) > 0) swap(b, c, size);
    if (compar(a, b) > 0) swap(a, b, size);
}

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *))
{
    char *lo, *hi;
    char *i, *j;

    while (nmemb > CUTOFF)
    {
        lo = (char *)base;
        hi = lo + (nmemb - 1) * size;

        /* Median-of-three: sort lo, mid, hi in place.
         * Then use mid as pivot and move it to hi-size
         * so it's out of the way during partitioning.
         * lo is already <= pivot and hi >= pivot, so
         * they serve as sentinels. */
        sort3(lo, lo + (nmemb / 2) * size, hi, size, compar);
        swap(lo + (nmemb / 2) * size, hi - size, size);

        /* Partition around pivot at hi-size.
         * i scans right looking for elements >= pivot.
         * j scans left looking for elements <= pivot.
         * lo is a sentinel (lo <= pivot).
         * hi is a sentinel (hi >= pivot). */
        i = lo;
        j = hi - size;

        for (;;)
        {
            do { i += size; } while (compar(i, hi - size) < 0);
            do { j -= size; } while (compar(j, hi - size) > 0);

            if (i >= j)
                break;

            swap(i, j, size);
        }

        /* Put pivot in its final position */
        swap(i, hi - size, size);

        /* Recurse on the smaller partition, loop on larger.
         * This limits stack depth to O(log n). */
        {
            size_t left_n = (i - (char *)base) / size;
            size_t right_n = nmemb - left_n - 1;

            if (left_n < right_n)
            {
                qsort(base, left_n, size, compar);
                base = i + size;
                nmemb = right_n;
            }
            else
            {
                qsort(i + size, right_n, size, compar);
                nmemb = left_n;
            }
        }
    }

    /* Insertion sort for the final small partition */
    if (nmemb > 1)
        isort((char *)base, nmemb, size, compar);
}
