#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct item_list {
  int item;
  struct list_head list;
};

int main() {
  struct item_list my_list;
  struct item_list *list_ptr;

  unsigned int i;

  INIT_LIST_HEAD(&my_list.list);

  for (i = 1; i<=10; i++) {
    list_ptr = (struct item_list *)malloc(sizeof (struct item_list));
    list_ptr->item = i;
    list_add(&(list_ptr->list), &(my_list.list));
  }

  list_for_each_entry(list_ptr, &my_list.list, list)
    printf("Item: %d\n", list_ptr->item);
  printf("\n");

  return 0;
}

