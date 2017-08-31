#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


#define N 64
#define M 256
typedef	struct client{
	int type;
	char name[N];
	char test[M];
}massage;
typedef struct sockaddr SA;
#define SIZE sizeof(massage)


int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr,peeraddr;
	socklen_t peerlen;
	int sockfd,nbyte;
	char buf[N];
	pid_t pid;
	massage massa;

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
	if((pid = fork()) <0)
	{
		perror("fail to fork");
		exit(-1);
	}
	else if(pid == 0)
	{
		while(1)
		{
			if(recvfrom(sockfd,&massa,SIZE,0,NULL,NULL) < 0)
			{
				perror("fail to recvfrom");
				exit(-1);
			}
			if(massa.type == 4)
			{
				if(strcmp(massa.test,"quit") == 0)
				{
					printf("[system] : system well be closed\n");
					kill(getppid(),SIGUSR1);
					exit(0);
				}

				else if(strcmp(massa.name ,"system") == 0)
				{
					printf("[%s] : %s\n",massa.name,massa.test);
				}
				else
				{
					printf("[system] :%s %s\n",massa.name,massa.test);
				}
			}
			else
			{
				printf("[%s] : %s\n",massa.name,massa.test);
			}
		}
	}
	else
	{
		printf("input the username:");
		fgets(buf,N,stdin);
		buf[strlen(buf)-1] = 0;
		strcpy(massa.name,buf);
		massa.type = 1;//新加入用户
		sendto(sockfd,&massa,SIZE,0,(SA *)&myaddr,sizeof(myaddr));//给系统发送信息；
		printf("***************Welcome to join chat rooms*************\n");

		while(1)
		{
			massa.type = 2;//表示正常发送
			fgets(massa.test,M,stdin);
			massa.test[strlen(massa.test)-1]=0;
			if(strcmp(massa.test,"quit") == 0)
			{
				massa.type = 3;//表示用户退出；
				sendto(sockfd,&massa,SIZE,0,(SA *)&myaddr,sizeof(myaddr));//给服务器发送退出信息；
				close(sockfd);
				kill(pid,SIGUSR1);
				wait(NULL);
				exit(0);
			}
			sendto(sockfd,&massa,SIZE,0,(SA *)&myaddr,sizeof(myaddr));
		}
	}
	return 0;
}

