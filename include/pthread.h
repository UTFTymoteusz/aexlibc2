#pragma once

#include <sys/types.h>

#define PTHREAD_CANCEL_ASYNCHRONOUS 1
#define PTHREAD_CANCEL_ENABLE 1
#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_DISABLE 0

#define PTHREAD_CANCELED ((void*) -1)

int pthread_attr_init(pthread_attr_t* attr);
int pthread_attr_destroy(pthread_attr_t* attr);

int  pthread_setcancelstate(int state, int* oldstate);
int  pthread_setcanceltype(int type, int* oldtype);
void pthread_testcancel();

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*),
                   void* arg);
int pthread_join(pthread_t thread, void** retval);
int pthread_cancel(pthread_t thread);

pthread_t pthread_self();
void      pthread_exit(void* retval);