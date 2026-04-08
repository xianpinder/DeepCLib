/*
 * bsearch.c - Binary search (C89)
 *
 * void *bsearch(const void *key, const void *base,
 *               size_t nmemb, size_t size,
 *               int (*compar)(const void *, const void *));
 *
 * Searches a sorted array of nmemb elements, each of size
 * bytes, for an element matching key. The comparator
 * receives the key as the first argument and the array
 * element as the second, per C89 §4.10.5.1.
 *
 * Returns a pointer to the matching element, or NULL if
 * not found. If multiple elements match, which one is
 * returned is unspecified.
 */

#include <stddef.h>

void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *))
{
    const char *cbase = (const char *)base;
    size_t lo, hi, mid;
    const char *item;
    int dir;

    lo = 0;
    hi = nmemb;

    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        item = cbase + mid * size;
        dir = (*compar)(key, item);
        if (dir < 0)
            hi = mid;
        else if (dir > 0)
            lo = mid + 1;
        else
            return (void *)item;
    }

    return NULL;
}
