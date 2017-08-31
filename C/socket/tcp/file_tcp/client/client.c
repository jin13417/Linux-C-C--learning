#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

typedef struct sockaddr SA;
#define N 64
void do_help()
{
	printf("help:       显示客户端所有的命令和说明\n");
	printf("list:       显示服务器端可下载的文件列表\n");
	printf("get<file>:  下载文件\n");
	printf("put<file>:  上传文件\n");
	printf("quit:       退出客户端\n");
}

void do_list(struct sockaddr_in serveraddr,char buf[N] ) 
{
	int sockfd,nbyte;

	if((sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	if(connect(sockfd,(SA *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}
	send(sockfd,buf,N,0);
	while((nbyte = recv(sockfd,buf,N,0)) > 0)
	{
		printf("%s\n",buf);
	}


}
void do_get(struct sockaddr_in serveraddr,char buf[N] ) 
{
	int sockfd,nbyte,fd;

	if((sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	if(connect(sockfd,(SA *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}
	send(sockfd,buf,N,0);
	fgets(buf,N,stdin);
	buf[strlen(buf)-1]='\0';
	send(sockfd,buf,N,0);
    


	while((nbyte = recv(sockfd,buf,N,0)) > 0)
	{
		
	}

void do_list(struct sockaddr_in serveraddr,char buf[N] ) 


int main(int argc,char *argv[])
{
	char buf[N];
	struct sockaddr_in serveraddr;

	if(argc < 3)
	{
		printf("input %s <sin_addr><sin_port>\n",argv[0]);
		exit(-1);
	}

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	while(1)
	{
		printf("client:\n");
		fgets(buf,N,stdin);
		if(strcmp(buf,"quit\n") == 0)
			exit(0);
		else if(strcmp(buf,"help\n") == 0)
			do_help();
		else if(strcmp(buf,"list\n") == 0)
			do_list(serveraddr,buf);
		else if(strcmp(buf,"get\n") == 0)
			do_get(serveraddr,buf);
		else if(strcmp(buf,"put\n") == 0)
			do_put(serveraddr,buf)

	}

	return 0;
}

