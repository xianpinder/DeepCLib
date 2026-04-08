#include <ctype.h>

/*
 * _AN = alphanumeric			isalnum()
 * _AL = alphabetic				isalpha()
 * _CT = control				iscntrl()
 * _DG = digit					isdigit()
 * _GR = graphic				isgraph()
 * _LO = lowercase letter		islower()
 * _PR = printable				isprint()
 * _PN = punctuation			ispunct()
 * _SP = space					isspace()
 * _UP = uppercase letter		isupper()
 * _HX = hexadecimal digit		isxdigit()
 *
 */

static unsigned int ascii_ctype[257] =
{
    0,						      					  /* EOF */
    _CT,                                              /*   0 */
    _CT,                                              /*   1 */
    _CT,                                              /*   2 */
    _CT,                                              /*   3 */
    _CT,                                              /*   4 */
    _CT,                                              /*   5 */
    _CT,                                              /*   6 */
    _CT,                                              /*   7 */
    _CT,                                              /*   8 */
    _CT | _SP,                                        /*   9 */
    _CT | _SP,                                        /*  10 */
    _CT | _SP,                                        /*  11 */
    _CT | _SP,                                        /*  12 */
    _CT | _SP,                                        /*  13 */
    _CT,                                              /*  14 */
    _CT,                                              /*  15 */
    _CT,                                              /*  16 */
    _CT,                                              /*  17 */
    _CT,                                              /*  18 */
    _CT,                                              /*  19 */
    _CT,                                              /*  20 */
    _CT,                                              /*  21 */
    _CT,                                              /*  22 */
    _CT,                                              /*  23 */
    _CT,                                              /*  24 */
    _CT,                                              /*  25 */
    _CT,                                              /*  26 */
    _CT,                                              /*  27 */
    _CT,                                              /*  28 */
    _CT,                                              /*  29 */
    _CT,                                              /*  30 */
    _CT,                                              /*  31 */
    _PR | _SP,                                        /*     */
    _GR | _PR | _PN,                                  /*  !  */
    _GR | _PR | _PN,                                  /*  "  */
    _GR | _PR | _PN,                                  /*  #  */
    _GR | _PR | _PN,                                  /*  $  */
    _GR | _PR | _PN,                                  /*  %  */
    _GR | _PR | _PN,                                  /*  &  */
    _GR | _PR | _PN,                                  /*  '  */
    _GR | _PR | _PN,                                  /*  (  */
    _GR | _PR | _PN,                                  /*  )  */
    _GR | _PR | _PN,                                  /*  *  */
    _GR | _PR | _PN,                                  /*  +  */
    _GR | _PR | _PN,                                  /*  ,  */
    _GR | _PR | _PN,                                  /*  -  */
    _GR | _PR | _PN,                                  /*  .  */
    _GR | _PR | _PN,                                  /*  /  */
    _AN | _DG | _GR | _PR | _HX,                      /*  0  */
    _AN | _DG | _GR | _PR | _HX,                      /*  1  */
    _AN | _DG | _GR | _PR | _HX,                      /*  2  */
    _AN | _DG | _GR | _PR | _HX,                      /*  3  */
    _AN | _DG | _GR | _PR | _HX,                      /*  4  */
    _AN | _DG | _GR | _PR | _HX,                      /*  5  */
    _AN | _DG | _GR | _PR | _HX,                      /*  6  */
    _AN | _DG | _GR | _PR | _HX,                      /*  7  */
    _AN | _DG | _GR | _PR | _HX,                      /*  8  */
    _AN | _DG | _GR | _PR | _HX,                      /*  9  */
    _GR | _PR | _PN,                                  /*  :  */
    _GR | _PR | _PN,                                  /*  ;  */
    _GR | _PR | _PN,                                  /*  <  */
    _GR | _PR | _PN,                                  /*  =  */
    _GR | _PR | _PN,                                  /*  >  */
    _GR | _PR | _PN,                                  /*  ?  */
    _GR | _PR | _PN,                                  /*  @  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  A  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  B  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  C  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  D  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  E  */
    _AN | _AL | _GR | _PR | _UP | _HX,                /*  F  */
    _AN | _AL | _GR | _PR | _UP,                      /*  G  */
    _AN | _AL | _GR | _PR | _UP,                      /*  H  */
    _AN | _AL | _GR | _PR | _UP,                      /*  I  */
    _AN | _AL | _GR | _PR | _UP,                      /*  J  */
    _AN | _AL | _GR | _PR | _UP,                      /*  K  */
    _AN | _AL | _GR | _PR | _UP,                      /*  L  */
    _AN | _AL | _GR | _PR | _UP,                      /*  M  */
    _AN | _AL | _GR | _PR | _UP,                      /*  N  */
    _AN | _AL | _GR | _PR | _UP,                      /*  O  */
    _AN | _AL | _GR | _PR | _UP,                      /*  P  */
    _AN | _AL | _GR | _PR | _UP,                      /*  Q  */
    _AN | _AL | _GR | _PR | _UP,                      /*  R  */
    _AN | _AL | _GR | _PR | _UP,                      /*  S  */
    _AN | _AL | _GR | _PR | _UP,                      /*  T  */
    _AN | _AL | _GR | _PR | _UP,                      /*  U  */
    _AN | _AL | _GR | _PR | _UP,                      /*  V  */
    _AN | _AL | _GR | _PR | _UP,                      /*  W  */
    _AN | _AL | _GR | _PR | _UP,                      /*  X  */
    _AN | _AL | _GR | _PR | _UP,                      /*  Y  */
    _AN | _AL | _GR | _PR | _UP,                      /*  Z  */
    _GR | _PR | _PN,                                  /*  [  */
    _GR | _PR | _PN,                                  /*  \  */
    _GR | _PR | _PN,                                  /*  ]  */
    _GR | _PR | _PN,                                  /*  ^  */
    _GR | _PR | _PN,                                  /*  _  */
    _GR | _PR | _PN,                                  /*  `  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  a  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  b  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  c  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  d  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  e  */
    _AN | _AL | _GR | _LO | _PR | _HX,                /*  f  */
    _AN | _AL | _GR | _LO | _PR,                      /*  g  */
    _AN | _AL | _GR | _LO | _PR,                      /*  h  */
    _AN | _AL | _GR | _LO | _PR,                      /*  i  */
    _AN | _AL | _GR | _LO | _PR,                      /*  j  */
    _AN | _AL | _GR | _LO | _PR,                      /*  k  */
    _AN | _AL | _GR | _LO | _PR,                      /*  l  */
    _AN | _AL | _GR | _LO | _PR,                      /*  m  */
    _AN | _AL | _GR | _LO | _PR,                      /*  n  */
    _AN | _AL | _GR | _LO | _PR,                      /*  o  */
    _AN | _AL | _GR | _LO | _PR,                      /*  p  */
    _AN | _AL | _GR | _LO | _PR,                      /*  q  */
    _AN | _AL | _GR | _LO | _PR,                      /*  r  */
    _AN | _AL | _GR | _LO | _PR,                      /*  s  */
    _AN | _AL | _GR | _LO | _PR,                      /*  t  */
    _AN | _AL | _GR | _LO | _PR,                      /*  u  */
    _AN | _AL | _GR | _LO | _PR,                      /*  v  */
    _AN | _AL | _GR | _LO | _PR,                      /*  w  */
    _AN | _AL | _GR | _LO | _PR,                      /*  x  */
    _AN | _AL | _GR | _LO | _PR,                      /*  y  */
    _AN | _AL | _GR | _LO | _PR,                      /*  z  */
    _GR | _PR | _PN,                                  /*  {  */
    _GR | _PR | _PN,                                  /*  |  */
    _GR | _PR | _PN,                                  /*  }  */
    _GR | _PR | _PN,                                  /*  ~  */
    _CT,                                              /* 127 */

   0, 0, 0, 0, 0, 0, 0, 0,			/* 128 - 135 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 136 - 143 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 144 - 151 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 152 - 159 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 160 - 167 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 168 - 175 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 176 - 183 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 184 - 191 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 192 - 199 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 200 - 207 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 208 - 215 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 216 - 223 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 224 - 231 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 232 - 239 */
   0, 0, 0, 0, 0, 0, 0, 0,			/* 240 - 247 */
   0, 0, 0, 0, 0, 0, 0, 0			/* 248 - 255 */
};



unsigned int *_CyTab = &ascii_ctype[1];
