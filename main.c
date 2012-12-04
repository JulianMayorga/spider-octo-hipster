#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "net.h"
#include "thpool.h"

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

struct work_args {
  char* host;
  int done_work;
  pthread_mutex_t* mutex;
};

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

void crawl(struct work_args *args) {
  net_fetch(args->host, "/");
  pthread_mutex_lock(args->mutex);
  args->done_work++;
  pthread_mutex_unlock(args->mutex);
  /*
   * file_save(content)
   */
}

int main(){
  int i;
  char* host = "www.google.com";

  struct work_args* args;
  
  args= (struct work_args*)malloc(sizeof(struct work_args)); 

  args->mutex = &work_mutex;
  args->done_work = 0;
  args->host = host;

  thpool_t* threadpool;             /* make a new thread pool structure     */
  threadpool=thpool_init(2);        /* initialise it to 4 number of threads */

  for (i=0; i<10; i++){
    thpool_add_work(threadpool, (void*)crawl, (void*)args);
  };

  puts("Will kill threadpool");
 
  while (10 > args->done_work) {
    sleep(1);
  }

  thpool_destroy(threadpool);

  return 0;
}
