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
	struct sockaddr_in serveraddr;
	int sockfd;
	char buf[64];

	if(argc < 3)
	{
		printf("input %s <sin_addr><sin_port>\n",argv[0]);
		exit(-1);
	}

	if((sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sockfd,(SA *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("fail to a ccept");
		exit(-1);
	}
	while(1)
	{
		printf("input the message:\n");
		fgets(buf,N,stdin);
		if(strcmp(buf,"quit\n") == 0)
		{
			close(sockfd);
			exit(0);
		}
		send(sockfd,buf,N,0);
		recv(sockfd,buf,N,0);
		printf("message : %s\n",buf);
	}

	return 0;
}

