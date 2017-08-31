#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct sockaddr SA;

int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr;
	int socketfd,nbyte;
	struct timeval tv = {5,0};

	if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) <0 )
	{
		perror("fail to socket");
		exit(-1);
	}

	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(socketfd,(SA *)&myaddr,sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	setsockopt(socketfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));

		if((nbyte = recvfrom(socketfd,(SA *)&myaddr,sizeof(myaddr),0,NULL,NULL)) < 0)
        {
			printf("errno = %d\n",errno);
			perror("fail to recvfrom");
			exit(-1);
		}
	return 0;
}



