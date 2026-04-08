#ifndef _SETJMP_H
#define _SETJMP_H

typedef struct {
    unsigned int sp;
    unsigned int ix;
    unsigned int ret_addr;
} jmp_buf[1];

int setjmp(jmp_buf);
void longjmp(jmp_buf, int);

#endif
