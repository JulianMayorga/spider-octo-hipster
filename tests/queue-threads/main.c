#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "thread.h"
#include <pthread.h>

struct item_list {
  int item;
  struct list_head list;
  pthread_mutex_t mutex;
};

void *queue_read(void *args) {
  struct item_list *thread_list = (struct item_list *) args;
  struct item_list *list_ptr;

  pthread_mutex_lock(&thread_list->mutex);
  list_ptr = list_entry(thread_list->list.prev, struct item_list, list);
  printf("Item: %d\n", list_ptr->item);
  list_del(thread_list->list.prev);
  printf("\n");
  printf("freeing item= %d", list_ptr->item);
  printf("\n");
  free(list_ptr);
  pthread_mutex_unlock(&thread_list->mutex);

  return NULL;
}

int main() {
  struct item_list my_list;
  struct list_head *pos, *q;
  struct item_list *list_ptr;

  unsigned int i;
  int return_value;
  pthread_t thread;

  INIT_LIST_HEAD(&my_list.list);
  pthread_mutex_init(&my_list.mutex, NULL);

  for (i = 1; i<=10; i++) {
    list_ptr = (struct item_list *)malloc(sizeof (struct item_list));
    list_ptr->item = i;
    list_add(&(list_ptr->list), &(my_list.list));
  }

  for (i = 1; i<=10; i++) {
    return_value = thread_create(&thread, queue_read, (void*) &my_list);
    if (return_value != 0) {
      perror("Guau!");
    }
  }

  pthread_join(thread, NULL);

  return 0;
}

