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
	struct sockaddr_in broadaddr,perraddr;
	char buf[N];
	int socketfd,peerlen;
    
	if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}


	bzero(&broadaddr,sizeof(broadaddr));
	broadaddr.sin_family = PF_INET;
	broadaddr.sin_port = htons(atoi(argv[2]));
	broadaddr.sin_addr.s_addr = inet_addr(argv[1]);
   if(bind(socketfd,(SA*)&broadaddr,sizeof(broadaddr)) < 0)
   {
	   perror("fail to bind");
	   exit(-1);
   }
    peerlen = sizeof(perraddr);
	while(1)
	{
		if(recvfrom(socketfd,buf,N,0,(SA *)&perraddr,&peerlen) < 0)
		{
			perror("fail to sendto");
			exit(-1);
		}
		printf("[%s:%d]:%s\n",inet_ntoa(perraddr.sin_addr),
				 ntohs(perraddr.sin_port),buf);
	}
	return 0;
}

