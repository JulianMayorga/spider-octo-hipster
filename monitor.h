/*
 * @file    monitor.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Monitor crawling
 */

#ifndef _MONITOR_

#define _MONITOR_

struct crawling_info {
  long mtype;
  char host[256];
  char url[512];
};

/* FUNCTIONS */

/*
 * @brief   Monitor crawling message receiving
 *
 * @param   key is the queue identifier
 * @return  0 on success,
 *         -1 on error
 */
int monitor_receive(key_t key);

/*
 * @brief   Monitor crawling message sending
 *
 * @param   msqid is the queue identifier
 * @param   host
 * @param   url
 * @return  0 on success,
 *         -1 on error
 */
int monitor_send(int msqid, char* host, char* url);

/*
 * @brief   Create monitor
 *
 * @return  msqid
 */
int monitor_create();

/*
 * @brief   Destroy monitor
 *
 * @param   msqid is the queue identifier
 * @return  0 on success,
 *         -1 on error
 */
int monitor_destroy(int msqid);

#endif
