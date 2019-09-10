#include "unp.h"
#include <time.h>

static int listenfd;
static pthread_t tid;
#define MAX_THREAD 10000
static int cur_thd = 0;
static pthread_t process_thd[MAX_THREAD];

void *process(void *connfd)
{
	time_t ticks = time(NULL);
	char buff[MAXLINE];
	
	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
	Write(*(int*)connfd, buff, strlen(buff));
	Close(*(int*)connfd);

	int res;
	pthread_exit((void*)&res);
}

void *front_reception()
{
	if (cur_thd == MAX_THREAD)
		cur_thd = 0;
	int connfd;
	
	while(1)
		{
			connfd = Accept(listenfd, (SA *) NULL, NULL);
			pthread_create(&(process_thd[cur_thd]), NULL, &process, (void*)&connfd);
			++cur_thd;
		}
}

int main(int argc, char **argv)
{
  struct sockaddr_in servaddr;
  time_t ticks;
	int i;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(13);

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

	pthread_create(&tid, NULL, &front_reception, NULL);
  for ( ; ; )
    {
			i++;
    }
}
