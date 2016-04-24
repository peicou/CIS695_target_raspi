/* Author: Francisco Sandoval */

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


#define BACKLOG 5     // max pending connections
#define QUEUESIZE 100 // max number of messages to keep in queue

#define MAXDATASIZE 100 // max number of bytes we can get at once 

/* 
 * queue - FIFO Structure to keep messages
 * buf - array to store messages
 * head, tail - pointers to first and last message
 * full, empty - flags to check queue status
 * mut - mutex to lock resource
 * notFull, notEmpty - pthread conditional flags
 */

typedef struct {
	int buf[QUEUESIZE];
	long head, tail;
	int full, empty;
	pthread_mutex_t *mut;
	pthread_cond_t *notFull, *notEmpty;
} queue;

/*
 * TCPServer - waits for connections, launched in POSIX thread
 * param - pointer to shared queue resource
 */

void *TCPServer (void *param);

/*
 * queueInit - returns a pointer to a queue structure
 */
queue *queueInit (void);

/*
 * queueDelete - deallocates and deletes the queue object
 * q - pointer to queue to finish
 */
void queueDelete (queue *q);

/*
 * queueAdd - adds a message to the queue
 * q - pointer to queue where the message will be added
 * in - message to be added
 */
void queueAdd (queue *q, int in);

/*
 * queueDel - deletes a message from the queue
 * q - queue to read and delete the message from
 * out - pointer to the deleted message
 */
void queueDel (queue *q, int *out);

/*
 * get_in_addr - 
 * sa - A sockaddr, this is an IPv4 or 6 address structure
 */
void *get_in_addr(struct sockaddr *sa);

/*
 * sigchld_handler - dead child reaper f(o.0)f  \(0.0)/
 * s - signal
 */
void sigchld_handler(int s);

#endif //_GUTIL_H_

