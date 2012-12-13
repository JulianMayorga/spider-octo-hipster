/*
 * @file    monitor.c
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Monitor crawl process
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monitor.h"

int monitor_receive(int msqid) {
  struct crawling_info info;

  for(;;) { /* Never quits! */
    if (msgrcv(msqid, &info, sizeof(info) - sizeof(long), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
    }
    printf("host: %s\nurl: %s\n---\n", info.host, info.url);
  }
  return 0;
}

int monitor_send(int msqid, char* host, char* url) {
  struct crawling_info info;

  strncpy(info.host, host, 256);
  strncpy(info.url, url, 512);

  info.mtype = 1;

  if (msgsnd(msqid, &info, sizeof(struct crawling_info) - sizeof(long), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }

  return 0;
}

int monitor_create() {
  int msqid;
  key_t key;

  if ((key = ftok("monitor.h", 'A')) == -1) {
    perror("ftok");
    exit(-1);
  }
  if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
    perror("msgget");
    exit(-1);
  }

  return msqid;
}

int monitor_destroy(int msqid) {
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(-1);
  }

  return 0;
}
