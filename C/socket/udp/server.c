#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct sockaddr SA;
#define N 64
int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr,peeraddr;
	socklen_t peerlen;
	int sockfd,nbyte;
	char buf[N];

	if(argc < 3)
	{
		printf("input %s <sin_addr><sin_port>\n",argv[0]);
		exit(-1);
	}
	if((sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(sockfd,(SA *)&myaddr,sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	while(1)
	{
		peerlen = sizeof(peeraddr);
		if((nbyte = recvfrom(sockfd,buf,N,0,(SA *)&peeraddr,&peerlen)) > 0)
		{
			printf("peeraddr.sin_addr.s_addr = %s,peeraddr.sin_port = %d\n",\
					inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
			printf("client massage is : %s\n",buf);
			sendto(sockfd,buf,N,0,(SA *)&peeraddr,peerlen);
		}
		else
		{
			perror("fail to recvfrom");
			exit(0);
		}

	}
	return 0;
}

