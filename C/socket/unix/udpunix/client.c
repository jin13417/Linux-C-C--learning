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

typedef struct sockaddr SA;
#define N 64

int main(int argc,char * argv[])
{
   struct sockaddr_un serveraddr,clientaddr;
   int socketfd,clientlen;
   char buf[N];

   if(argc < 3)
   {
	   printf("Uasge : %s <serverpath><clientpath>\n",argv[0]);
	   exit(-1);
   }
   if((socketfd = socket(PF_UNIX,SOCK_DGRAM,0)) < 0)
   {
	   perror("fail to socket");
	   exit(-1);
   }

   bzero(&clientaddr,sizeof(clientaddr));
   clientaddr.sun_family = PF_UNIX;
   strcpy(clientaddr.sun_path,argv[2]);
    remove(argv[2]);
   if(bind(socketfd,(SA*)&clientaddr,sizeof(clientaddr)) < 0)
   {
	   perror("fail to bind");
       exit(-1);
   }
   bzero(&serveraddr,sizeof(serveraddr));
   serveraddr.sun_family = PF_UNIX;
   strcpy(serveraddr.sun_path,argv[1]);

   while(1)
   {
	   printf("client >\n");
	   fgets(buf,N,stdin);
	   buf[strlen(buf) - 1] = 0;
	   if(strcmp(buf,"quit") == 0)break;
	   sendto(socketfd,buf,N,0,(SA *)&serveraddr,sizeof(serveraddr));
	   if(recvfrom(socketfd,buf,N,0,NULL,NULL) < 0)
	   {
		   perror("fail to recvfrom");
		   exit(-1);
	   }
	   printf("[massage from server] : %s\n",buf);
   }
   close(socketfd);
   return 0;
}




