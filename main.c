#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

#include "net.h"
#include "list.h"
#include "file.h"
#include "thpool.h"
#include "url_frontier.h"
#include "monitor.h"
#include "utils.h"

#define THREADS_MAX 512

pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

void crawl(struct url_list *url_list) {
  char* buffer = NULL;
  struct url_list* url_list_ptr = (struct url_list*) url_list;
  struct url_list* tmp_ptr;
  char* host = NULL;
  char* url = NULL;

  if (list_empty(&url_list_ptr->list) != 1) {

    //start of mutex
    pthread_mutex_lock(url_list_ptr->mutex);

    //store current node in local variable
    tmp_ptr = list_entry(url_list_ptr->list.prev, struct url_list, list);

    //put this inside a mutex
    //because we are dealing with a list shared among threads
    host = calloc(strlen(tmp_ptr->host), 1);
    url = calloc(strlen(tmp_ptr->url), 1);

    //store host and url in local variables
    host = strcpy(host, tmp_ptr->host);
    url = strcpy(url, tmp_ptr->url);
    monitor_send(url_list->msqid, host, url);
    
    //free current node of the list
    list_del(&tmp_ptr->list);
    free(tmp_ptr);

    //end of mutex
    pthread_mutex_unlock(url_list->mutex);

    //fetch url
    buffer = net_fetch(host, url);
    //printf("finished crawling host:%s\nurl:%s\n", host, url);

    //save file to disk
    if ( -1 == file_save(buffer, host, url) ) {
      perror("file_save");
      exit(1);
    }
  }
}

int main(int argc, char **argv) {

  int msqid = monitor_create();

  if ( -1 == msqid ) {
    perror("monitor_create");
  }
  
  if (!fork()) {
    //child
    if( -1 == monitor_receive(msqid) ) {
      perror("monitor_receive");
      exit(1);
    }

  } else {
    //parent
    int i;
    int number_of_entries = 0;
    struct url_list url_list;
	char filename[512];
	
	// Initialize filename with all zeros	
	bzero(filename, sizeof(filename));
	
	// Manage arguments
	utils_manage_args(argc, argv, &number_of_entries, filename);
    
	INIT_LIST_HEAD(&url_list.list);

    url_list.mutex = &work_mutex;

    url_list.msqid = msqid;
	
	if (strcmp(filename, "") == 0) {
		snprintf(filename, sizeof(filename), "url_frontier"); // Set default
	}	

	// Set how many entries from file gonna read
	if (number_of_entries == 0) {
    	number_of_entries = url_frontier_parse(filename, &url_list);
	} else {
 		url_frontier_parse(filename, &url_list);
	}

    if (number_of_entries > THREADS_MAX) {
      number_of_entries = THREADS_MAX;
    }

    pthread_t thread[number_of_entries];

    for (i = 0; i < number_of_entries; i++){
      if (0 != pthread_create(&thread[i], NULL, (void*)crawl, (void*)&url_list)) {
        perror("pthread_create");
      }
    }

    for (i = 0; i < number_of_entries; i++) {
      if (0 != pthread_join(thread[i], NULL)) {
        perror("pthread_join");
      }
    }
  }
  

  return 0;
}
