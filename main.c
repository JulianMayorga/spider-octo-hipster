#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "thread.h"

void * get(void *args) {
printf("GET http://nave.com\n");
return NULL;
}

int main() {
int return_value;
pthread_t thread;
return_value = thread_create(&thread, get, NULL);
if (return_value != 0) {
perror("Guau!");
}
pthread_join(thread, NULL);

return 0;

}
