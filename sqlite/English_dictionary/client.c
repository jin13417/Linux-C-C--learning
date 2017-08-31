#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 256
#define NAMESIZE 16

typedef struct sockaddr SA;

typedef struct {
	char type;
	char name[NAMESIZE];
	char data[BUFSIZE];
}MSG;

	MSG massage;
void do_help()
{
	printf("***********************************\n");
	printf("          1 : Register\n");
	printf("          2 : Login\n");
	printf("          3 : Quit\n");
	printf("***********************************\n");
}

void do_register(int socketfd,MSG massage)
{
	char buf[BUFSIZE];

	massage.type = 'R';

	puts("please input your name:");
	fgets(massage.name,NAMESIZE,stdin);
	massage.name[strlen(massage.name) - 1] = '\0';
	puts("please input your passswd");
	fgets(massage.data,BUFSIZE,stdin);
	massage.data[strlen(massage.data) - 1] = '\0';

	if(send(socketfd,&massage,sizeof(massage),0) < 0)
	{
		perror("fail to send");
		exit(-1);
	}
	if(recv(socketfd,&massage,BUFSIZE,0) < 0)
	{
		perror("fail to recv");
		exit(-1);
	}
	if(strncmp(massage.data,"Y",1) == 0)
	{
		printf("Register Success!\n");
		puts("welcome to use online_English_dictionary!");
		do_help();
	}
	else
	{
		printf("%s\n",massage.data);
		printf("Register Failure!please Register again!\n");
		do_help();
	}
}

void do_login(int socketfd,MSG massage)
{
	char buf[BUFSIZE];

	massage.type = 'L';

	puts("please input your name:");
	fgets(massage.name,NAMESIZE,stdin);
	massage.name[strlen(massage.name) - 1] = '\0';
	puts("please input your passswd");
	fgets(massage.data,BUFSIZE,stdin);
	massage.data[strlen(massage.data) - 1] = '\0';

	if(send(socketfd,&massage,sizeof(massage),0) < 0)
	{
		perror("fail to send");
		exit(-1);
	}
	recv(socketfd,&massage,BUFSIZE,0);

	switch (massage.data[0])
	{
	case 'N':
		printf("%s\n",massage.data);
		printf("登录失败～请重新输入用户名和密码:\n");
		do_help();
		break;
	case 'Y':
		printf("Login Success!\n");
		puts("      欢迎使用在线英英词典！");
	default:
		printf("%s\n",massage.data);
		printf("登录失败～请重新输入用户名和密码:\n");
		do_help();
	}
}

void do_help1()
{
	printf("***********************************\n");
	printf("          1 : Query\n");
	printf("          2 : History\n");
	printf("          3 : Quit\n");
	printf("***********************************\n");
}
void do_query(int socketfd,MSG massage)
{
	massage.type = 'Q';
   while(1)
   {
	puts("pleale input the words");
	fgets(massage.data,BUFSIZE,stdin);
	massage.data[strlen(massage.data) -1 ] = '\0';
    if(strncmp(massage.data,"#",2) ==0)break;
	send(socketfd,&massage,BUFSIZE,0);
	recv(socketfd,&massage,BUFSIZE,0);
	printf("%s\n",massage.data);
   }
	do_help1();

}
void do_history(int socketfd,MSG massage)
{
	massage.type = 'H';
	send(socketfd,&massage,BUFSIZE,0);
	while(recv(socketfd,&massage,BUFSIZE,0) > 0)
		printf("%s\n",massage.data);
}

int main(int argc,char *argv[])
{
	struct sockaddr_in serveraddr;
	int socketfd,n,login = 0;
	char buf[BUFSIZE];

	if(argc <3)
	{
		printf("Usage %s <IP><port>\n",argv[0]);
		exit(-1);
	}

	if((socketfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	//填充服务器地址：
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	//建立链接：
	if(connect(socketfd,(SA *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}
	do_help();
	while ((scanf("%d%*c",&n) == 1)&&n!=3)
	{
		switch (n)
		{
		case 1:
			do_register(socketfd,massage);
			break;
		case 2:
			do_login(socketfd,massage);
			break;
		case 3:
			break;
		default :
			do_help(); break;
		}
	}
    do_help1();
	while ((scanf("%d%*c",&n) == 1)&&n!=3)
	{
		switch (n)
		{
		case 1:
			do_query(socketfd,massage);
			break;
		case 2:
			do_history(socketfd,massage);
			break;
		case 3:
			break;
		default :
			do_help1(); break;
		}
	}

	return 0;
}



