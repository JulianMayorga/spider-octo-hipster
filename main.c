#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "net.h"
#include "file.h"
#include "thpool.h"

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

struct work_args {
  char* host;
  int done_work;
  pthread_mutex_t* mutex;
};

void crawl(struct work_args *args) {
  char* buffer = NULL;

  //fetch url
  buffer = net_fetch(args->host, "/");
  //save file to disk
  if ( -1 == file_save(buffer, "google") ) {
    perror("file_save");
  }
  pthread_mutex_lock(args->mutex);
  args->done_work++;
  pthread_mutex_unlock(args->mutex);
}

int main(){
  int i;
  char* host = "www.google.com";
  char* buffer;

  buffer = net_fetch(host, "/");
  //save file to disk
  if ( -1 == file_save(buffer, "index.html") ) {
    perror("file_save");
  }

 /* struct work_args* args;
  
  args= (struct work_args*)malloc(sizeof(struct work_args)); 

  args->mutex = &work_mutex;
  args->done_work = 0;
  args->host = host;
  */

//  thpool_t* threadpool;             /* make a new thread pool structure     */
//  threadpool=thpool_init(2);        /* initialise it to 4 number of threads */
/*
  for (i=0; i<10; i++){
    thpool_add_work(threadpool, (void*)crawl, (void*)args);
  };

  puts("Will kill threadpool");
 
  while (10 > args->done_work) {
    sleep(1);
  }

  thpool_destroy(threadpool);
  */

  return 0;
}
