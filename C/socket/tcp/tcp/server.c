#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

typedef struct sockaddr SA;

#define N 64
int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr,peeraddr;
	socklen_t peerlen;
	int listenfd,confd;
	char buf[64];

	if(argc < 3)
	{
		printf("input %s <sin_addr><sin_port>\n",argv[0]);
		exit(-1);
	}

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
		perror("fail to bind");
		exit(-1);
	}
	listen(listenfd,10);
	peerlen = sizeof(peeraddr);
	while(1)
	{
		if((confd = accept(listenfd,(SA *)&peeraddr,&peerlen)) < 0)
		{
			perror("fail to a ccept");
			exit(-1);
		}
		printf("peeraddr.sin_addr.s_addr = %s,peeraddr.sin_port = %d\n",\
				inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
		while(1)
		{
			if(recv(confd,buf,N,0) > 0)
			{
				send(confd,buf,N,0);
			}
			else
			{
				close(confd);
				break;
			}
		}
	}
	return 0;
}

