#ifndef _THREAD_

#define _THREAD_

#include <pthread.h>

int thread_create(pthread_t * thread, void * start_routine, void * args);

#endif
