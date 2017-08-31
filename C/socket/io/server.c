#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  N  64

typedef struct sockaddr SA;

int main(int argc, char *argv[])
{
	int listenfd, connfd, maxfd, i, nbyte;
	struct sockaddr_in myaddr;
	char buf[N];
	fd_set rdfs, rdfs_bak;

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		return -1;
	}

	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (bind(listenfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	listen(listenfd, 10);

	maxfd = listenfd;
	FD_ZERO(&rdfs_bak);
	FD_SET(listenfd, &rdfs_bak);

	while ( 1 )
	{
		rdfs = rdfs_bak;
		if (select(maxfd+1, &rdfs, NULL, NULL, NULL) < 0)
		{
			perror("fail to select");
			exit(-1);
		}
		for (i=0; i<=maxfd; i++)
		{
			if (FD_ISSET(i, &rdfs))
			{
				if (i == listenfd)
				{
					connfd = accept(i, NULL, NULL);
					FD_SET(connfd, &rdfs_bak);
					if (connfd > maxfd) maxfd = connfd;
				}
				else
				{
					if ((nbyte = recv(i, buf, N, 0)) <= 0)
					{
						FD_CLR(i, &rdfs_bak);
						close(i);
					}
					else
					{
						send(i, buf, nbyte, 0);
					}
				} // endif 
			}
		}  // end for 
	}

	return 0;
}
