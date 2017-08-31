#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define N 64

int main(int argc,char *argv[])
{
	struct sockaddr_in broadaddr;
	char buf[N];
	int socketfd, n = 1;
    
	if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	if(setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,&n,sizeof(n)) < 0)
	{
		perror("fail to setsockopt");
		exit(-1);
	}

	bzero(&broadaddr,sizeof(broadaddr));
	broadaddr.sin_family = PF_INET;
	broadaddr.sin_port = htons(atoi(argv[2]));
	broadaddr.sin_addr.s_addr = inet_addr(argv[1]);

	while(1)
	{
		printf("please input the broadcast massage:\n");
		fgets(buf,N,stdin);
		buf[strlen(buf) - 1] = 0;
		if(sendto(socketfd,buf,N,0,(SA *)&broadaddr,sizeof(broadaddr)) < 0)
		{
			perror("fail to sendto");
			exit(-1);
		}
	}
	return 0;
}

