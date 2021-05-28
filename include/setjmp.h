#pragma once

struct jmp_buf {
    int test;
};

#define jmp_buf struct jmp_buf

int  setjmp(jmp_buf env);
void longjmp(jmp_buf env, int value);