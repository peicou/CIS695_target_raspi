#ifndef _GUTIL_H_
#define _GUTIL_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h> 
#include <malloc.h> 
#include <math.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


#define BACKLOG 5     // how many pending connections queue will hold
#define QUEUESIZE 100

 #define MAXDATASIZE 100 // max number of bytes we can get at once 

typedef struct {
	int buf[QUEUESIZE];
	long head, tail;
	int full, empty;
	pthread_mutex_t *mut;
	pthread_cond_t *notFull, *notEmpty;
} queue;

void *TCPServer (void *param);

queue *queueInit (void);
void queueDelete (queue *q);
void queueAdd (queue *q, int in);
void queueDel (queue *q, int *out);

void *get_in_addr(struct sockaddr *sa);
void sigchld_handler(int s);

#endif //_GUTIL_H_

