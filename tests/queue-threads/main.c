#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "thread.h"
#include <pthread.h>

struct item_list {
  int item;
  struct list_head list;
};

void *print_items(void *args) {
  struct item_list *thread_list = (struct item_list *) args;
  struct item_list *list_ptr;

  list_for_each_entry(list_ptr, &thread_list->list, list) {
    printf("Item: %d\n", list_ptr->item);
  }
  printf("\n");

  return NULL;
}

int main() {
  struct item_list my_list;
  struct item_list *list_ptr;

  unsigned int i;
  int return_value;

  INIT_LIST_HEAD(&my_list.list);

  for (i = 1; i<=10; i++) {
    list_ptr = (struct item_list *)malloc(sizeof (struct item_list));
    list_ptr->item = i;
    list_add(&(list_ptr->list), &(my_list.list));
  }

  pthread_t thread;
  return_value = thread_create(&thread, print_items, (void*) &my_list);
  if (return_value != 0) {
    perror("Guau!");
  }
  pthread_join(thread, NULL);

  return 0;
}

