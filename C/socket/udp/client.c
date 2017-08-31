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

	while(1)
	{
		printf("input the massage:\n");
		fgets(buf,N,stdin);
		buf[strlen(buf)-1] = 0;
		if(strcmp(buf,"quit") == 0)
		{
			close(sockfd);
			exit(0);
		}
		sendto(sockfd,buf,N,0,(SA *)&myaddr,sizeof(myaddr));
		if(recvfrom(sockfd,buf,N,0,NULL,NULL) > 0)
			printf("massage is :  %s\n",buf);


	}
	return 0;
}

