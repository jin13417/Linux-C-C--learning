#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct sockaddr SA;
#define N 64
void do_list(int confd)
{
	DIR *dp;
    struct drient *ep;
	dp = opendir(".");
		while((ep =readdir(dp)) != NULL)
		{
			if(ep -> d_name[0] != '.')
			{
				send(confd,ep -> d_name,N,0);
			}
		}
		closedir(dp);
}

int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr,peeraddr;
	socklen_t peerlen;
	int listenfd,confd;
    char buf[N];
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
		resv(confd,buf,N,0);
		if(strcmp(buf,"list\n") == 0)
			do_list(confd);
	}
	return 0;
}

