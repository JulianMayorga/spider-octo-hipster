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
#include <mqueue.h>
#include <errno.h>


#include "monitor.h"

/*int monitor_receive(int msqid) {
  struct crawling_info info;
  for(;;) { // Never quits!
    if (msgrcv(msqid, &info, sizeof(info) - sizeof(long), 0, 0) == -1) {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
    printf("host: %s\nurl: %s\n---\n", info.host, info.url);
  }
  return 0;
}*/

int monitor_receive() {
	struct mq_attr attr;
	mqd_t mqd;
	char host[256];
	
	//Create monitor
	mqd = monitor_create();
	
	if ( -1 == mqd ) {
    	perror("monitor_create");
 	 }
	mq_getattr(mqd, &attr);
	
	for(;;) { // Never quits!
		if ( (mq_receive(mqd, host, attr.mq_msgsize,NULL) ) != 0) {
			
			// 11 means an EAGAIN error, that is because of the non-blocking flag when queue is created
			if (11 == errno) {
				printf("Queue temporaly empty, let's wait some messages :)\n");
				exit(EXIT_FAILURE);
			}
			perror("mq_receive");
			exit(EXIT_FAILURE);
	}
		printf("Received host: %s\n---\n", host);
	}
	mq_close(mqd);
	return 0;
}

/*int monitor_send(int msqid, char* host, char* url) {
  struct crawling_info info;

  strncpy(info.host, host, 256);
  strncpy(info.url, url, 512);

  info.mtype = 1;

  if (msgsnd(msqid, &info, sizeof(struct crawling_info) - sizeof(long), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }

  return 0;
}*/

int monitor_send(char *host) {
	struct crawling_info info;
	mqd_t mqd;
	
	struct mq_attr attr;
	mqd = monitor_create();
	if ( -1 == mqd ) {
    	perror("monitor_create");
 	 }

	mq_getattr(mqd, &attr);
	strncpy(info.host, host, 256);
	//strncpy(info.url, url, 512);
	info.mqd = mqd;

	if (0 > mq_send(info.mqd, info.host, sizeof(info.host), 0)) {
		perror("mq_send");
		exit(1);	
	}
	printf("Sended host: %s\n", info.host);
	mq_close(mqd);
	return 0;
}

/*int monitor_create() {
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
}*/

int monitor_create() {
	mqd_t qd;
	
	// The O_NONBLOCK flag is for throw error EAGAIN because the queue is empty
	qd = mq_open("/monitor", O_RDWR | O_CREAT | O_NONBLOCK, 0666, NULL);
	if ( qd == -1) {
		perror("mq_open");
		exit(1);
	}
	return qd;
}

/*int monitor_destroy(int msqid) {
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(-1);
  }

  return 0;
}*/

int monitor_destroy() {
	if (-1 == mq_unlink("/monitor")) {
		perror("mq_link");
		exit(EXIT_FAILURE);
	}
	return 0;
}
