#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

typedef struct sockaddr SA;

void handler(int siganl)
{
	return;
}

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
     struct sigaction act;
	 sigaction(SIGALRM,NULL,&act);
	 act.sa_handler = handler;
	 act.sa_flags &= ~SA_RESTART;
	 sigaction(SIGALRM,&act,NULL);
	 alarm(5);

		if((nbyte = recvfrom(socketfd,(SA *)&myaddr,sizeof(myaddr),0,NULL,NULL)) < 0)
        {
			printf("errno = %d\n",errno);
			perror("fail to recvfrom");
			exit(-1);
		}
	return 0;
}



