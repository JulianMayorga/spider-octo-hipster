/*
 * @file    url_frontier.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing utilities for the url frontier
 */

#ifndef _URL_FRONTIER_

#define _URL_FRONTIER__

struct url_list {
  char* host;
  char* url;
  int msqid;
  struct list_head list;
  pthread_mutex_t* mutex;
};

/* FUNCTIONS */

/*
 * @brief   parse urls file
 *
 * @param   name of urls file
 * @param   url in memory list
 * @return  void
 */

int url_frontier_parse(char* filename, struct url_list* url_list);

#endif
