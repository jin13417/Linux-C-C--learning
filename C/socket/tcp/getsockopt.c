#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>


int main()
{
	int socketfd;

	if((socketfd = socket(PF_INET,SOCK_STREAM,0)) <0)
	{
		perror("fail to socket");
		exit(-1);
	}
	int a;
	socklen_t b = sizeof(a);
	getsockopt(socketfd,SOL_SOCKET,SO_SNDBUF,&a,&b);
	printf("the bufsize is %d\n",a);
	return 0;
}
