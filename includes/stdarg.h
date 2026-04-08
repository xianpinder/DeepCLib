#ifndef _STDARG_H
#define _STDARG_H

#ifndef _VA_LIST
#define _VA_LIST
typedef char *va_list;
#endif

/* Round size up to stack slot boundary (3 bytes) */
#define __va_rounded(type) (((sizeof(type) + 2) / 3) * 3)

/* va_start: initialize ap to point to first variadic argument
 * last is the last named parameter before the ...
 */
#define va_start(ap, last) \
    ((ap) = (char *)&(last) + __va_rounded(last))

/* va_arg: get next argument of given type and advance ap
 * Uses comma operator: advance ap, then return value from old position
 */
#define va_arg(ap, type) \
    (*(type *)((ap) += __va_rounded(type), (ap) - __va_rounded(type)))

/* va_end: cleanup (nothing to do) */
#define va_end(ap) ((void)0)

/* va_copy: copy va_list state */
#define va_copy(dest, src) ((dest) = (src))

#endif
