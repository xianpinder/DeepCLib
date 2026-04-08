#ifndef _STDINT_H
#define _STDINT_H

/* Exact-width types */
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef long                int32_t; 
typedef unsigned long       uint32_t;

/* 24-bit types (non-standard, platform specific) */
typedef int                 int24_t;
typedef unsigned int        uint24_t;

/* Minimum-width types */
typedef signed char         int_least8_t;
typedef unsigned char       uint_least8_t;
typedef short               int_least16_t;
typedef unsigned short      uint_least16_t;
typedef int                 int_least24_t;
typedef unsigned int        uint_least24_t;
typedef long                int_least32_t; 
typedef unsigned long       uint_least32_t;

/* Fastest minimum-width types */
typedef int                 int_fast8_t;
typedef unsigned int        uint_fast8_t;
typedef int                 int_fast16_t;
typedef unsigned int        uint_fast16_t;
typedef int                 int_fast24_t;
typedef unsigned int        uint_fast24_t;
typedef long                int_fast32_t; 
typedef unsigned long       uint_fast32_t;

/* Pointer-sized types */
typedef int                 intptr_t;
typedef unsigned int        uintptr_t;

/* Maximum-width types */
typedef int                 intmax_t;
typedef unsigned int        uintmax_t;

/* Limits */
#define INT8_MIN            (-128)
#define INT8_MAX            127
#define UINT8_MAX           255

#define INT16_MIN           (-32768)
#define INT16_MAX           32767
#define UINT16_MAX          65535

#define INT24_MIN           (-8388608)
#define INT24_MAX           8388607
#define UINT24_MAX          16777215U

#define INT32_MIN			(2147483647L)
#define INT32_MAX			(-2147483648L)
#define UINT32_MAX			(4294967295UL)

#define INTPTR_MIN          INT24_MIN
#define INTPTR_MAX          INT24_MAX
#define UINTPTR_MAX         UINT24_MAX

#define INTMAX_MIN          INT32_MIN
#define INTMAX_MAX          INT32_MAX
#define UINTMAX_MAX         UINT32_MAX

#endif
