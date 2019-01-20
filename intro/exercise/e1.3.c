/*
  Before you running this program, you must running server end 
  program firstly, named p41.c in the same directory. So your 
  output should be like this:

  Server end:
  pqy@sda1:~/UNP/bin$ sudo ./p41 //listening

  Client end:
  pqy@sda1:~/UNP/bin$ ./p36 127.0.0.1
  Fri Dec  9 21:59:13 2016
  
  
 */

#include "unp.h"

int main(int argc, char **argv)
{
  int sockfd, n;
  char recvline[MAXLINE + 1];
  struct sockaddr_in servaddr;

  if (argc != 2)
    err_quit("usage: a.out <Internet Protocol Address>");

  if ( (sockfd = socket(9999, SOCK_STREAM, 0)) < 0)
		{
			printf("%d\n", errno);
			err_sys("socket error");
		}

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(13);
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    err_quit("internet port error for %s", argv[1]);

  if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    err_sys("connect error");

  while ( (n = read(sockfd, recvline, MAXLINE)) > 0)
    {
      recvline[n] = 0;
      if (fputs(recvline, stdout) == EOF)
	err_sys("puts error");
    }
  if (n < 0)
    err_sys("read error");
  
  exit(0);
}
