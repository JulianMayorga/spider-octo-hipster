#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "net.h"
#include "list.h"
#include "file.h"
#include "thpool.h"

#define WORK_TOTAL 3

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

struct url_list {
  char* host;
  char* url;
  struct list_head list;
  pthread_mutex_t* mutex;
};

void crawl(struct url_list *url_list) {
  char* buffer = NULL;
  struct url_list* url_list_ptr = (struct url_list*) url_list;
  struct url_list* tmp_ptr;

  if (list_empty(&url_list_ptr->list) != 1) {
    printf("Mutex:%d\n", (int)url_list_ptr->mutex);
    pthread_mutex_lock(url_list_ptr->mutex);
    tmp_ptr = list_entry(url_list_ptr->list.prev, struct url_list, list);
    //fetch url
    buffer = net_fetch(tmp_ptr->host, tmp_ptr->url);
    //save file to disk
    if ( -1 == file_save(buffer, tmp_ptr->host, tmp_ptr->url) ) {
      perror("file_save");
      exit(1);
    }
    list_del(&tmp_ptr->list);
    free(tmp_ptr);
    pthread_mutex_unlock(url_list->mutex);
  }
}

int main(){
  int i;
  struct url_list url_list, *url_list_ptr, *url_list_ptr2, *url_list_ptr3;
  char* host = "www.google.com";
  char* url = "/index.html";

  INIT_LIST_HEAD(&url_list.list);

  thpool_t* threadpool;             /* make a new thread pool structure     */
  threadpool=thpool_init(2);        /* initialise it to x number of threads */

  url_list.mutex = &work_mutex;

  url_list_ptr = (struct url_list *)malloc(sizeof(struct url_list));
  url_list_ptr->host = host;
  url_list_ptr->url = url;

  list_add(&(url_list_ptr->list), &(url_list.list));

  url_list_ptr2 = (struct url_list *)malloc(sizeof(struct url_list));
  url_list_ptr2->host = "www.altavista.com";
  url_list_ptr2->url = "/index.html";

  list_add(&(url_list_ptr2->list), &(url_list.list));

  url_list_ptr3 = (struct url_list *)malloc(sizeof(struct url_list));
  url_list_ptr3->host = "www.guialocal.com.ar";
  url_list_ptr3->url = "/index.html";

  list_add(&(url_list_ptr3->list), &(url_list.list));
  for (i=0; i<WORK_TOTAL; i++){
    thpool_add_work(threadpool, (void*)crawl, (void*)&url_list);
  };

  while (list_empty(&url_list.list) != 1) {
    sleep(1);
  }

  thpool_destroy(threadpool);

  return 0;
}
