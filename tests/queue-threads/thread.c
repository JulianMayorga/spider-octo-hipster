#include "thread.h"

int thread_create(pthread_t * thread, void * start_routine, void * args) {
  int return_value;

  return_value = pthread_create(thread, NULL, start_routine, args);

  return return_value;
}
