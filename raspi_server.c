/*
** Author - Francisco Sandoval
 * Interfacing the UE4 TCPComponent with a simple embedded target
 * CIS695
*/
#include "gUtil.h"

void *App (void *param)
{
	int msg = 2;
	queue *fifo;
	fifo = (queue *)param;
	
	system("gpio mode 0 out");

	for (;;)
	{
		if(!fifo->empty)
		{
			pthread_mutex_lock(fifo->mut);
			queueDel(fifo, &msg);
			pthread_mutex_unlock(fifo->mut);
			pthread_cond_signal(fifo->notFull);
			//printf("app: received %i\n", msg);
		}
		if (0 == msg)
		{
			system("gpio write 0 0");
			printf("lights off!\n");
			msg=2;
		} else if (1 == msg)
		{
			system("gpio write 0 1");	
			printf("lights on!\n");
			msg=2;
		}
	}
	return (NULL);
}


int main(int argc, char *argv[])
{
    int port = 0;
	
	if (argc !=2)
	{
		printf("Usage: ./rs <port number>\n");
		return 1;
	}

	port = atoi(argv[1]);

	if (port<2000 || port>65535)
	{
		printf("port must be an integer between 2000 and 65535\n");
		printf("invalid value %i", port);
		return 1;
	}

	queue *fifo;
	pthread_t srv, app;

	fifo = queueInit();
	if (fifo==NULL)
	{
		printf("queueInit failed\n");
		exit (1);
	}
	queueAdd(fifo, port);

	pthread_create(&srv, NULL, TCPServer, fifo);
	pthread_create(&app, NULL, App, fifo);
	pthread_join(srv, NULL);
	pthread_join(app, NULL);

	queueDelete(fifo);
	
	return 0;
}
