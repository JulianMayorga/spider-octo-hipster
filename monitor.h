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
  mqd_t mqd;
  char host[256];
  //char url[512];
};

/* FUNCTIONS */

/*
 * @brief   Monitor crawling message receiving
 *
 * @return  0 on success,
 *         -1 on error
 */
//int monitor_receive(key_t key);
int monitor_receive();

/*
 * @brief   Monitor crawling message sending
 *
 * @param   host
 * @return  0 on success,
 *         -1 on error
 */
//int monitor_send(int msqid, char* host, char* url);

int monitor_send(char *host);

/*
 * @brief   Create monitor
 *
 * @return  msqid
 */
int monitor_create();

/*
 * @brief   Destroy monitor
 *
 * @return  0 on success,
 *         -1 on error
 */
//int monitor_destroy(int msqid);
int monitor_destroy();
#endif
