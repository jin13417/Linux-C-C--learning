#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 64

typedef struct sockaddr SA;

int main(int argc,char *argv[])
{
	int  i ,listenfd,connfd,maxfd;
	char buf[N];
	fd_set rdfs;
	struct sockaddr_in myaddr;

	if((listenfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
		{
			perror("fail to socket");
			exit(-1);
		}
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(listenfd,(SA *)&myaddr,sizeof(myaddr)) < 0)
	{
		perror("fail to bing");
		exit(-1);
	}
	listen(listenfd,10);
	maxfd =listenfd;
	while(1)
	{
		FD_ZERO(&rdfs);
		FD_SET(0,&rdfs);
		FD_SET(listenfd,&rdfs);

		if(select(maxfd+1,&rdfs,NULL,NULL,NULL) < 0)
		{
			perror("fail to select");
			exit(-1);
		}
		for(i= 0;i<=maxfd;i++)
		{
			if(FD_ISSET(i,&rdfs))
			{
				if(i == STDIN_FILENO)
				{
					fgets(buf,N,stdin);
					printf("%s",buf);
				}
				else if(i == listenfd)
				{
					connfd = accept(listenfd,NULL , NULL);
					printf("NEW Connection connfd is coming \n");
					close(connfd);
				}
			}
		}
	}
	return 0;
}

