#include "stdlib.h"
#include "string.h"
#include "sys/signal.h"
#include "syscallids.h"
#include "unistd.h"

void (**atexit_array)() = NULL;
int atexit_count        = 0;

int atexit(void (*func)()) {
    atexit_count++;
    atexit_array = (void (**)()) realloc(atexit_array, sizeof(void*) * atexit_count);

    memcpy(atexit_array + 1, atexit_array + 0, (atexit_count - 1) * sizeof(void*));
    atexit_array[0] = func;

    return 0;
}

void exit(int status) {
    for (int i = 0; i < atexit_count; i++)
        atexit_array[i]();

    syscall(SYS_EXIT, status);
}

void abort() {
    kill(getpid(), SIGABRT);
}