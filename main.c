#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "net.h"
#include "list.h"
#include "file.h"
#include "thpool.h"
#include "url_frontier.h"

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

void crawl(struct url_list *url_list) {
  char* buffer = NULL;
  struct url_list* url_list_ptr = (struct url_list*) url_list;
  struct url_list* tmp_ptr;
  char* host = NULL;
  char* url = NULL;

  if (list_empty(&url_list_ptr->list) != 1) {
    pthread_mutex_lock(url_list_ptr->mutex);
    printf("Entering lock from thread %d\n", (int)pthread_self());
    tmp_ptr = list_entry(url_list_ptr->list.prev, struct url_list, list);
    host = calloc(strlen(tmp_ptr->host), 1);
    url = calloc(strlen(tmp_ptr->url), 1);
    host = strcpy(host, tmp_ptr->host);
    url = strcpy(url, tmp_ptr->url);
    list_del(&tmp_ptr->list);
    free(tmp_ptr);
    pthread_mutex_unlock(url_list->mutex);
    //fetch url
    buffer = net_fetch(host, url);
    printf("host:%s\nurl:%s\n", host, url);
    printf("Leaving lock from thread %d\n", (int)pthread_self());
    //save file to disk
    if ( -1 == file_save(buffer, host, url) ) {
      perror("file_save");
      exit(1);
    }
  }
}

int main(){
  int i;
  int number_of_entries = 0;
  struct url_list url_list;

  INIT_LIST_HEAD(&url_list.list);

  thpool_t* threadpool;             /* make a new thread pool structure     */
  threadpool=thpool_init(5);        /* initialise it to x number of threads */

  url_list.mutex = &work_mutex;

  number_of_entries = url_frontier_parse("url_frontier", &url_list);

  printf("%d\n", number_of_entries);

  
  for (i=0; i<number_of_entries; i++){
    thpool_add_work(threadpool, (void*)crawl, (void*)&url_list);
  };
  

  while (list_empty(&url_list.list) != 1) {
    sleep(1);
  }
  

  thpool_destroy(threadpool);

  return 0;
}
