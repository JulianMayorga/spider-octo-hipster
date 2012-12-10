/*
 * @file    url_frontier.c
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing utilities for the url frontier
 */

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "list.h"
#include "url_frontier.h"

int url_frontier_parse(char* filename, struct url_list* url_list) {
  char* url_buffer = NULL;
  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j;
  int number_of_entries = 0;

  struct url_list* url_list_ptr;

  url_buffer = file_to_buffer(filename);

  printf("url_buffer:%s\n", url_buffer);

  for (j = 1, str1 = url_buffer; ; j++, str1 = NULL) {
    token = strtok_r(str1, ";", &saveptr1);
    if (token == NULL)
      break;
    //crear nuevo nodo de la lista
    url_list_ptr = (struct url_list*)malloc(sizeof(struct url_list));

    str2 = token;
    subtoken = strtok_r(str2, ",", &saveptr2);

    //asigna a host
    url_list_ptr->host = subtoken;
    printf(" --> %s\n", subtoken);

    subtoken = strtok_r(NULL, ",", &saveptr2);
    //asigna a url
    url_list_ptr->url = subtoken;
    printf(" --> %s\n", subtoken);
    list_add(&(url_list_ptr->list), &url_list->list);
    number_of_entries++;
  }
  
  return number_of_entries;
}
