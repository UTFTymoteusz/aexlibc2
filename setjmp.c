#include "setjmp.h"

#include "syscallids.h"
#include "unistd.h"

int setjmp(jmp_buf env) {
    syscall(SYS_PANIC);
    return 0;
}

void longjmp(jmp_buf env, int val) {
    syscall(SYS_PANIC);
}