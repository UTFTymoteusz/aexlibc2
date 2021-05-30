#include "errno.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "sys/signal.h"
#include "syscallids.h"
#include "unistd.h"

void (**atexit_array)() = NULL;
int   atexit_count      = 0;
int   env_len           = 2048;
char* env_buffer        = NULL;

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

bool getenvline(int index) {
    if (!env_buffer)
        env_buffer = (char*) malloc(env_len);

    while (syscall(SYS_GETENV, index, env_buffer, env_len) == -1 && errno == ERANGE)
        env_buffer = (char*) realloc(env_buffer, env_len *= 2);

    return errno != EINVAL;
}

char* getenv(const char* name) {
    size_t name_len = strlen(name);

    for (int i = 0; getenvline(i); i++) {
        if (memcmp(name, env_buffer, name_len) != 0 || env_buffer[name_len] != '=')
            continue;

        return env_buffer + name_len + 1;
    }

    return NULL;
}