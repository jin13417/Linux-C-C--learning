#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>

typedef struct sockaddr SA;
#define N 64
#define M 1
void handler(int signal)
{
	return;
}

int main(int argc,char * argv[])
{
   struct sockaddr_un serveraddr,clientaddr;
   int socketfd,clientlen;
   char buf[N];
   struct sigaction act;

   if(argc < 2)
   {
	   printf("Uasge : %s <serverpath>\n",argv[0]);
	   exit(-1);
   }
   if((socketfd = socket(PF_UNIX,SOCK_DGRAM,0)) < 0)
   {
	   perror("fail to socket");
	   exit(-1);
   }

   bzero(&serveraddr,sizeof(serveraddr));
   serveraddr.sun_family = PF_UNIX;
   strcpy(serveraddr.sun_path,argv[1]);
    remove(argv[1]);
   if(bind(socketfd,(SA*)&serveraddr,sizeof(serveraddr)) < 0)
   {
	   perror("fail to bind");
       exit(-1);
   }
   
   clientlen = sizeof(clientaddr);
#if M
	   sigaction(SIGALRM,NULL,&act);//获得当前信号 并保存到ACT结构体中
	   act.sa_handler = handler;//设置结构体内参数
	   act.sa_flags &= ~SA_RESTART;
	   sigaction(SIGALRM,&act,NULL);//捕捉SIGALRM信号
#endif

   while(1)
   {
	   alarm(20);
	   if(recvfrom(socketfd,buf,N,0,(SA *)&clientaddr,&clientlen) < 0)
      {
		  printf("the client is outline\n");
		  perror("fail to recvfrom");
		  continue;
	  }
	   printf("[%s] : %s\n",clientaddr.sun_path,buf);
	   sendto(socketfd,buf,N,0,(SA *)&clientaddr,sizeof(clientaddr));
   }
   return 0;
}




