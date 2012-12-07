#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "net.h"
#include "file.h"
#include "thpool.h"

#define WORK_TOTAL 1

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

struct work_args {
  char* host;
  char* url;
  int done_work;
  pthread_mutex_t* mutex;
};

void crawl(struct work_args *args) {
  char* buffer = NULL;
  char* fullpath = NULL;
  static char* sites_dir = "sites/";

  fullpath = (char*)calloc(strlen(sites_dir) + strlen(args->host) + strlen(args->url) + 1, 1);
  //fetch url
  buffer = net_fetch(args->host, args->url);
  pthread_mutex_lock(args->mutex);
  //create host dir
  strncat(fullpath, sites_dir, strlen(sites_dir));
  strncat(fullpath, args->host, strlen(args->host));
  if ( -1 == mkdir(fullpath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ) {
    perror("mkdir");
    exit(1);
  }
  //form file path
  strncat(fullpath, args->url, strlen(args->url));
  //save file to disk
  if ( -1 == file_save(buffer, fullpath) ) {
    perror("file_save");
    exit(1);
  }
  args->done_work++;
  pthread_mutex_unlock(args->mutex);
}

int main(){
  int i;
  char* host = "www.google.com";
  char* url = "/index.html";

  struct work_args* args;

  args= (struct work_args*)malloc(sizeof(struct work_args)); 

  args->mutex = &work_mutex;
  args->done_work = 0;
  args->host = host;
  args->url = url;

  thpool_t* threadpool;             /* make a new thread pool structure     */
  threadpool=thpool_init(2);        /* initialise it to x number of threads */

  for (i=0; i<WORK_TOTAL; i++){
    thpool_add_work(threadpool, (void*)crawl, (void*)args);
  };

  while (WORK_TOTAL > args->done_work) {
    sleep(1);
  }

  thpool_destroy(threadpool);

  return 0;
}
