#include "setjmp.h"

#include "syscallids.h"
#include "unistd.h"

int setjmp(jmp_buf) {
    syscall(SYS_PANIC);
    return 0;
}

void longjmp(jmp_buf, int) {
    syscall(SYS_PANIC);
}