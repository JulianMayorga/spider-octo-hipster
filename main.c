#include <stdio.h>

#include "thpool.h"

/* Some arbitrary task 1 */
void task1(){
  printf("# Thread working: %u\n", (int)pthread_self());
  printf("  Task 1 running..\n");
}

/* Some arbitrary task 2 */
void task2(int a){
  printf("# Thread working: %u\n", (int)pthread_self());
  printf("  Task 2 running..\n");
  printf("%d\n", a);
}

int main(){
  int i;

  thpool_t* threadpool;             /* make a new thread pool structure     */
  threadpool=thpool_init(4);        /* initialise it to 4 number of threads */

  puts("Adding 20 tasks to threadpool");
  int a=54;
  for (i=0; i<10; i++){
    thpool_add_work(threadpool, (void*)task1, NULL);
    thpool_add_work(threadpool, (void*)task2, (void*)a);
  };

  puts("Will kill threadpool");
  thpool_destroy(threadpool);

  return 0;
}
