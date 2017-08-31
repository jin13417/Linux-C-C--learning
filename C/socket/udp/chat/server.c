#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
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
typedef struct node{
	struct sockaddr_in peeraddr;
	struct node *next;
}linknode,*linklist;

linklist creatlinklist()//创建链表
{
	linklist l;
	l = (linklist)malloc(sizeof(linknode));
	l -> next = NULL;
	return l;
}

void visitlinklist(linklist l,int sockfd,massage *p)//遍历链表
{
	l = l ->next;
	while(l != NULL)
	{
		sendto(sockfd,p,SIZE,0,(SA *)&(l -> peeraddr),sizeof(l -> peeraddr));
		l = l ->next;
	}
}

void insertlinklist(linklist l,struct sockaddr_in x)//插入链表
{
	linklist q;
	q = (linklist)malloc(sizeof(linknode));
	q -> peeraddr = x;
	q -> next = l -> next;
	l -> next = q;
}
void deletelinklist(linklist l,struct sockaddr_in x)//删除链表
{
	linklist q;
	q = l -> next;
	while(q != NULL)
	{
		if(q -> peeraddr.sin_port == x.sin_port)
		{
			l ->next = q -> next;
			free(q);
		}
		else
		{
			l =l -> next;
			q = l -> next;
		}
	}
}

int main(int argc,char *argv[])
{
	struct sockaddr_in myaddr,x;
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

	if(bind(sockfd,(SA *)&myaddr,sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	if((pid = fork()) <0)
	{
		perror("fail to fork");
		exit(-1);
	}
	else if(pid == 0)//子进程
	{
		linklist l;
		l = creatlinklist();
		peerlen =sizeof(x);
		while(1)
		{
			recvfrom(sockfd,&massa,SIZE,0,(SA *)&x,&peerlen);
			switch(massa.type)
			{
			case 1:
				strcpy(massa.test,"is online");
				massa.type = 4;
				insertlinklist(l,x);
				visitlinklist(l,sockfd,&massa);
				break;
			case 2:
				visitlinklist(l,sockfd,&massa);
				break;
			case 3:
				deletelinklist(l,x);
				strcpy(massa.test,"is outline");
				massa.type = 4;
				visitlinklist(l,sockfd,&massa);
				break;
			case 4:
				visitlinklist(l,sockfd, &massa);
				break;
			}
		}


	}
	else
	{
		while(1)//父进程
		{
			massa.type = 4;//表示是系统发送的；
			strcpy(massa.name,"system");
			fgets(massa.test,M,stdin);
			massa.test[strlen(massa.test) -1] = 0;
			if(strcmp(massa.test,"quit") == 0)
			{
				sendto(sockfd,&massa,SIZE,0,(SA *)&myaddr,sizeof(myaddr));
				sleep(1);
				kill(pid,SIGUSR1);
				wait(NULL);
				exit(0);
			}
			else
			{
				sendto(sockfd,&massa,SIZE,0,(SA *)&myaddr,sizeof(myaddr));
			}
		}
	}
	return 0;
}

