#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 64
//多路复用IO
typedef struct sockaddr SA;

int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr;
	int listenfd,connectfd,i,nbyte,maxfd;
	char buf[N];
	fd_set rdfs ,rdfsh;

	if(argc < 3)
	{
		printf("Usage:%s <ip><port>\n",argv[0]);
		exit(-1);
	}
	if((listenfd = socket(PF_INET,SOCK_STREAM,0)) < 0)//创建套接字
	{
		perror("fail to socket");
		exit(-1);
	}
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(listenfd, (SA *)&myaddr,sizeof(myaddr)) < 0)//绑定
	{
		perror("fail to bind");
		exit(-1);
	}
	listen(listenfd,10);//设置监听模式
	FD_ZERO(&rdfsh);//置0
	FD_SET(listenfd,&rdfsh);//将vlistenfd 加入到vrdfsh中
	maxfd = listenfd;

	while(1)
	{
		rdfs = rdfsh;
		if(select(maxfd+1,&rdfs,NULL,NULL,NULL) < 0)
		{
			perror("fail to select");
			exit(-1);
		}

		for(i=0;i<=maxfd;i++)
		{
			if(FD_ISSET(i,&rdfs))
			{
				if(i == listenfd)
				{
					if((connectfd = accept(listenfd,NULL,NULL)) < 0)
					{
						perror("fail to accept");
						exit(-1);
					}
					FD_SET(connectfd,&rdfsh);
					if(connectfd > maxfd)
						maxfd = connectfd;
				}
				else
				{
					if((nbyte = recv(i,buf,N,0)) > 0)
					{
						send(i,buf,nbyte,0);
					}
					else
					{
						FD_CLR(i,&rdfsh);
						close(i);
					}
				}
			}
		}
	}
	return 0;
}





